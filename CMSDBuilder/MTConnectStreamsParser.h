//
// MTConnectStreamsParser.h
//

#pragma once

//#import <msxml6.dll>
#include <string>
#include <vector>
#include <map>
#include "StdStringFcn.h"

#include <AtlComTime.h>
#include "atlutil.h"

#include <boost/function.hpp> 
#include <boost/function_equal.hpp> 

enum TimeFormat
{
  HUM_READ,
  GMT,
  GMT_UV_SEC,
  LOCAL
};
extern std::string GetTimeStamp(TimeFormat format=GMT_UV_SEC);
extern COleDateTime GetDateTime(std::string s);
class less_NoCaseString
{
public:
	bool operator() (const std::string& x, const std::string& y) const
	{return (stricmp( x.c_str(), y.c_str() )<0); }
};


struct StreamData
{
	COleDateTime	datetime;
	int				sequence;
	std::string		value;
	std::string		name;
	int				nMsTimeinState;
	StreamData(std::string	_name="", std::string _value="", std::string timestamp="", std::string _sequence=""):
	name(_name),value(_value) 
	{
		if(!timestamp.empty())
			datetime=GetDateTime(timestamp);
		sequence=ConvertString<int>(_sequence, 0);
		nMsTimeinState=0;
	}

};

class StreamDataDictionary :  public std::map<std::string, StreamData> 
{
public:
	typedef std::map<std::string, StreamData>  Mapping;
	std::string GetNamedValue(std::string name)
	{
		Mapping::iterator it=	this->find(name);
		if(it!= this->end())
			return (*it).second.value;
		return "";
	}
};

/**
	MTConnectStreamsParser parser;
	parser.AddMTConnectDevice("127.0.0.1/M1");
	parser.Start();
	Sleep(10000);
	parser.Stop();
	parser.Join(2000);
*/

// name, type, id
typedef std::map<std::string, std::string, less_NoCaseString> DataDictionary;
//typedef std::map<std::string, StreamData> StreamDataDictionary;
typedef std::map<COleDateTime, DataDictionary > TimedDataDictionary;
typedef boost::function<void (StreamDataDictionary)> FcnDataNotify;

class CMTConnectStreamsParser :
	public IWorkerThreadClient
{
	MSXML2::IXMLDOMSchemaCollectionPtr m_pSchemaCache;
	MSXML2::IXMLDOMDocumentPtr         m_pXSDDoc;
	MSXML2::IXMLDOMDocument2Ptr        m_pXMLDoc;
	// Handling the device specification or probe?
	std::string _devicesfilename;
	TimedDataDictionary timeddata;
	DataDictionary _lastprobedata;
	COleDateTime _lasttimestamp; 
	ULONG dwSamplingInterval;

	std::string errmsg;
	StreamDataDictionary data;
	CHandle						_hJoinMutex;
	HANDLE						_hTimer;
	CWorkerThread<>				_workerthread;
	bool						_bInitialized;
	bool						_bClear;


public:

	CMTConnectStreamsParser(void);
	~CMTConnectStreamsParser(void);
	std::string  ParseXMLDocument(_bstr_t xmlfile, _bstr_t xsdfile="", _bstr_t xsdname="");
	std::map<std::string, std::string> TagRenames;
	std::map<std::string, StreamDataDictionary> mappeddata;
	std::map<std::string, std::vector<FcnDataNotify>> listeners;

	_bstr_t GetAttribute(MSXML2::IXMLDOMNodePtr node, _bstr_t attribute);
	HRESULT ReadStream(std::string url, StreamDataDictionary &data, int nMsPeriod=1000);
	void						DumpData(StreamDataDictionary data);
	HRESULT						Execute(DWORD_PTR dwParam, HANDLE hObject);
	HRESULT						CloseHandle(HANDLE);
	void						AddMTConnectDevice(std::string url);
	void						AddNotification(std::string url, FcnDataNotify);
	void						RemoveMTConnectDevice(std::string url);
	StreamDataDictionary		GetData(std::string url) { return mappeddata[url]; }



	void						Initialize();
	void						Start();
	void						Stop();
	bool						Join(int nWait);
	void						Clear();
};
__declspec(selectany)  CMTConnectStreamsParser MTConnections;
