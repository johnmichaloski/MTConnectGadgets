//
// MTConnectStreamsParser.h
//
// DISCLAIMER:
// This software was developed by U.S. Government employees as part of
// their official duties and is not subject to copyright. No warranty implied 
// or intended.

#pragma once

//#pragma comment( lib, "msxml2.lib" )
#import <msxml6.dll>
#include <string>
#include <vector>
#include <map>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <AtlComTime.h>

#include "StdStringFcn.h"

using namespace boost::posix_time;
using namespace boost::gregorian;

extern ptime GetDateTime(std::string s);

struct StreamData
{
	std::string		value;
	std::string		name;
	std::string		category;
	std::string		type;
	std::string		subtype;
	std::string		units;
	std::string		nativeunits;
	std::string		timestamp;
	std::string		sequence;

	void Normalize()
	{
		if(!timestamp.empty())
			_datetime=GetDateTime(timestamp);
		_sequence=ConvertString<int>(sequence, 0);
	}

	ptime			_datetime;
	int				_sequence;
};

class less_NoCaseString
{
public:
	bool operator() (const std::string& x, const std::string& y) const
	{return (stricmp( x.c_str(), y.c_str() )<0); }
};

class DataDictionary : public std::map<std::string, std::string, less_NoCaseString> 
{
public:
	typedef std::map<std::string, std::string, less_NoCaseString>  DataDictionaryBaseType;
	DataDictionary& operator=(const std::map<std::string, std::string>& base)
	{
		clear();
		insert(base.begin(), base.end());
		return *this;
	}
	std::vector<std::string> Keys()
	{
		std::vector<std::string> v;
		for(DataDictionaryBaseType::iterator it = begin(); it != end(); ++it) 
			v.push_back(it->first);
		return v;
	}
	std::vector<std::string> Values()
	{
		std::vector<std::string> v;
		for(DataDictionaryBaseType::iterator it = begin(); it != end(); ++it) 
			v.push_back(it->second);
		return v;
	}
	std::vector<std::string> ValueList(std::vector<std::string> fields)
	{
		std::vector<std::string> tmp;
		for(int i=0; i< fields.size(); i++)
			tmp.push_back( this->operator [](fields[i]));
		return tmp;
	}
	std::string ValueCsvString(std::string csvfields)
	{
		return CsvString(ValueList(TrimmedTokenize(csvfields,",")));
	}
	void Mixin(std::vector<std::string> items, std::string defaultVal)
	{
		for(int i=0; i< items.size(); i++)
				this->operator [](items[i]) = defaultVal;
	}
	void SelectiveMerge(std::vector<std::string> itemlist, DataDictionary & itemstomerge)
	{
		for(int i=0; i< itemlist.size(); i++)
			this->operator [](itemlist[i]) = itemstomerge[itemlist[i]];
	}
	static std::string DataDictionary::HrMinSecFormat(int sec)
	{
		return StdStringFormat("%02d:%02d:%02d", sec/3600,  (sec%3600)/60,  sec%60);
	}
	static std::string DataDictionary::HrMinSecFormat(double dsec){	return HrMinSecFormat((int) dsec);}	

	template<typename T>
	std::vector<T> Column( std::vector<DataDictionary> data, std::string column)
	{
		std::vector<T> items;
		for(int i=0; i< data.size(); i++)
		{
			try{
			items.push_back(ConvertString<T>(data[i][column], T()));
			}
			catch(...){}
		}
		return items;
	}
	inline std::string CsvString(std::vector<std::string> &list)
	{
		std::string tmp;
		for(int i=0; i<list.size(); i++) 
			tmp+=(i>0)? "," : "" + list[i];
		return tmp;
	}
};

// name, type, id
typedef std::map<std::string, StreamData> StreamDataDictionary;
typedef std::map<ptime, DataDictionary > TimedDataDictionary;

class MTConnectStreamsParser
{
	MSXML2::IXMLDOMSchemaCollectionPtr m_pSchemaCache;
	MSXML2::IXMLDOMDocumentPtr         m_pXSDDoc;
	MSXML2::IXMLDOMDocument2Ptr        m_pXMLDoc;
	std::string							_devicesfilename;
	StreamDataDictionary				streamdata;
	TimedDataDictionary					timeddata;
	DataDictionary						_lastprobedata;
	ptime								_lasttimestamp; 
	StreamDataDictionary				laststreamdata;

public:
	static std::map<std::string, std::string>		_TagRenames;
	static std::vector<std::string> 				_saveddata;
	static std::map<std::string, std::string>		_valuerenames;

public:
	MTConnectStreamsParser(void);
	~MTConnectStreamsParser(void);

	_bstr_t						GetAttribute(MSXML2::IXMLDOMNodePtr node, _bstr_t attribute);
	void						Release();
	std::string					ParseXMLDocument(_bstr_t xmlfile, _bstr_t xsdfile="", _bstr_t xsdname="");
	DataDictionary				ParseDataItems();
	std::vector<DataDictionary> ReadStream(std::string filename);
	static std::string			GetMTConnectUrl(std::string ippath);
};
