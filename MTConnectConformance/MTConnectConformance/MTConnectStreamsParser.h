//
// MTConnectStreamsParser.h
//

#pragma once

#pragma comment( lib, "msxml6.lib" )
#import <msxml6.dll>

#include <string>
#include <vector>
#include <map>
#include "StdStringFcn.h"
#include "DataDictionary.h"
#include <comdef.h>

#include "boost/date_time/posix_time/posix_time.hpp"
#include <AtlComTime.h>

using namespace boost::posix_time;
using namespace boost::gregorian;

extern ptime GetDateTime(std::string s);

struct StreamData
{
	ptime	datetime;
	int				sequence;
	std::string		value;
	std::string		name;
	StreamData(std::string	_name="", std::string _value="", std::string timestamp="", std::string _sequence=""):
	name(_name),value(_value) 
	{
		if(!timestamp.empty())
			datetime=GetDateTime(timestamp);
		sequence=ConvertString<int>(_sequence, 0);
	}

};


// name, type, id
typedef std::map<std::string, StreamData> StreamDataDictionary;
typedef std::map<ptime, DataDictionary > TimedDataDictionary;

class MTConnectStreamsParser
{
	MSXML2::IXMLDOMDocumentPtr         m_pXSDDoc;
	MSXML2::IXMLDOMDocument2Ptr        m_pXMLDoc;
	ptime								_lasttimestamp; 

public:
	MTConnectStreamsParser(void);
	~MTConnectStreamsParser(void);

	_bstr_t						GetAttribute(MSXML2::IXMLDOMNodePtr node, _bstr_t attribute);
	void						Release();
	std::string					ParseXMLDocument(_bstr_t xmlfile, _bstr_t xsdfile="", _bstr_t xsdname="");
};
