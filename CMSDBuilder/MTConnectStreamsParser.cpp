//
// CMTConnectStreamsParser.cpp
//

#include "StdAfx.h"
#include "MTConnectStreamsParser.h"
//#pragma comment( lib, "msxml2.lib" )

COleDateTime GetDateTime(std::string s)
{
	// parse 2012-02-03T17:31:51.0968Z 
	int Year, Month, Day, Hour, Minute, Second, Millisecond;
	if(sscanf(s.c_str(), "%d-%d-%dT%d:%d:%d.%d", &Year, &Month, &Day, &Hour, &Minute,&Second, &Millisecond)==7){}
		//12/2/2009 2:42:25 PM
	else if(sscanf(s.c_str(), "%d/%d/%4d%d:%d:%d", &Month, &Day, &Year,  &Hour, &Minute,&Second)==6){}
	else throw std::exception("Unrecognized date-time format\n");

	 //return ptime( date(Year,Month,Day),
  //                hours(Hour)  +
  //                minutes(Minute) +
  //                seconds(Second) +
  //                boost::posix_time::millisec(int(Millisecond)) );

	return COleDateTime( Year, Month, Day, Hour, Minute, Second ); 
}

std::string GetTimeStamp(TimeFormat format)
{
  SYSTEMTIME st;
  char timestamp[64];
  GetSystemTime(&st);
  sprintf(timestamp, "%4d-%02d-%02dT%02d:%02d:%02d", st.wYear, st.wMonth,
    st.wDay, st.wHour, st.wMinute, st.wSecond);
  
  if (format == GMT_UV_SEC)
  {
    sprintf(timestamp + strlen(timestamp), ".%04dZ", st.wMilliseconds);
  }
  else
  {
    strcat(timestamp, "Z");
  }
  
  return timestamp;
}
static _bstr_t checkParseError(MSXML2::IXMLDOMParseErrorPtr pError)
{
	_bstr_t parseError =_bstr_t("At line ")+ _bstr_t(pError->Getline()) + _bstr_t("\n")+ _bstr_t(pError->Getreason());
	//MessageBox(NULL,parseError, "Parse Error",MB_OK);
	return parseError;

}

static 	void dump_com_error(_com_error &e)
{
	::AtlTrace("Error\n");
	//TRACE1("\a\tCode = %08lx\n", e.Error());
	//TRACE1("\a\tCode meaning = %s", e.ErrorMessage());
	_bstr_t bstrSource(e.Source());
	_bstr_t bstrDescription(e.Description());
	::AtlTrace("\a\tSource = %s\n", (LPCSTR) bstrSource);
	::AtlTrace("\a\tDescription = %s\n", (LPCSTR) bstrDescription);
}
	

CMTConnectStreamsParser::CMTConnectStreamsParser(void)
{
	_workerthread.Initialize();
	dwSamplingInterval=2000;
	_bClear=false;

}

CMTConnectStreamsParser::~CMTConnectStreamsParser(void)
{

}

_bstr_t CMTConnectStreamsParser::GetAttribute(MSXML2::IXMLDOMNodePtr node, _bstr_t attribute)
{
	_bstr_t text= L"";;
	CComPtr<MSXML2::IXMLDOMNamedNodeMap> attributes;
	node->get_attributes( &attributes );
	if( attributes ) 
	{
		MSXML2::IXMLDOMNodePtr attr = attributes->getNamedItem(attribute);
		if(attr==NULL)
			return text;
		if(attr->nodeValue.vt == VT_BSTR)
			return attr->nodeValue.bstrVal;
	}

	return text;
}

std::string CMTConnectStreamsParser::ParseXMLDocument(_bstr_t xmlfile, _bstr_t xsdfile, _bstr_t xsdname)
{ 
	_bstr_t parseError(L"");
	try{
		IXMLDOMParseErrorPtr  pError;

		// load the XML file
		// ****** you need to use IXMLDOMDocument2 interface *********
		HRESULT hr = m_pXMLDoc.CreateInstance(__uuidof(MSXML2::DOMDocument));
		m_pXMLDoc->async =  VARIANT_FALSE; 

		hr = m_pXMLDoc->load(xmlfile);      

		//check on the parser error      
		if(hr!=VARIANT_TRUE)
		{
			return (LPCSTR) checkParseError(m_pXMLDoc->parseError);
		}
	}
	catch(_com_error &e)
	{
		errmsg=e.ErrorMessage();
		dump_com_error(e);
		return  e.ErrorMessage();
	}

	return (LPCSTR) parseError;
}
// Replace into data with newer from data
static DataDictionary  Merge(DataDictionary &into, DataDictionary &from)
{
	DataDictionary newdata = into;
	for(DataDictionary::iterator it=from.begin(); it!=from.end(); it++)
	{
		into[(*it).first]=(*it).second;
	}
	return newdata;
}

HRESULT CMTConnectStreamsParser::ReadStream(std::string url, StreamDataDictionary &data, int nMsPeriod)
{
//	TimedDataDictionary::iterator _attimestamp =timeddata.end(); 

	_devicesfilename = "http://" + url + "/current";

	// Not empty means error
	if(!ParseXMLDocument(_devicesfilename.c_str()).empty())
		return E_FAIL;

	try
	{
		MSXML2::IXMLDOMNodePtr root = m_pXMLDoc->GetdocumentElement();
		MSXML2::IXMLDOMNodeListPtr nodes = root->selectNodes(_bstr_t("//DeviceStream"));
		for(int i=0; i< nodes->length; i++)
		{
			MSXML2::IXMLDOMNodePtr pNode = NULL;					
			nodes->get_item(i, &pNode);

			_bstr_t items[2] = {_bstr_t(".//Samples"), _bstr_t(".//Events") };
			for(int ii=0; ii<2 ; ii++)
			{
				MSXML2::IXMLDOMNodeListPtr samples = pNode->selectNodes(items[ii]);
				for(int j=0; j< samples->length; j++)
				{
					MSXML2::IXMLDOMNodePtr pSampleHive = NULL;					
					samples->get_item(j, &pSampleHive);

					// Get each child
					MSXML2::IXMLDOMNodeListPtr childs = pSampleHive->childNodes;
					for(int k=0; k< childs->length; k++)
					{
						MSXML2::IXMLDOMNodePtr pSample = NULL;
						COleDateTime datetime;
						std::string name ;
						std::string timestamp;
						std::string sequence;

						childs->get_item(k, &pSample);
						name = (LPCSTR)  GetAttribute(pSample, "name");
						if(name.empty())
							name = (LPCSTR)  GetAttribute(pSample, "dataItemId");
						if(name.empty())
							continue;
						timestamp = (LPCSTR)  GetAttribute(pSample, "timestamp");
						sequence = (LPCSTR)  GetAttribute(pSample, "sequence");

						// Lookup any name remapping to shorten
						if(TagRenames.find(name)!= TagRenames.end())
						{
							name = TagRenames[name];
						}
						std::string value =(LPCSTR) pSample->Gettext();
						StreamData olddata = data[name];
						StreamData newdata(name,value, timestamp, sequence);
						if(olddata.value == value)
							newdata.nMsTimeinState+=nMsPeriod;
						else
							newdata.nMsTimeinState=0;

						data[name]=newdata;
#if 0
						if(!timestamp.empty())
						{
							datetime=GetDateTime(timestamp);
							DataDictionary & dict(timeddata[datetime]) ;
							dict[name]=data[name];
							//for(DataDictionary::iterator it=dict.begin(); it!=dict.end(); it++)
							//{
							//	OutputDebugString(StdStringFormat("%s %s=%s\n", timestamp.c_str(), 
							//		(*it).first.c_str(), (*it).second.c_str()).c_str());
							//}
						}

#endif
					}
				}
			}
		}
	}
	catch(...)
	{
		errmsg = "CMTConnectStreamsParser::ParseDataItems() Exception\n";
		return E_FAIL;
	}
	return S_OK;

}


void  CMTConnectStreamsParser::DumpData(StreamDataDictionary data)
{
	for(StreamDataDictionary::iterator it = data.begin(); it!=data.end(); it++)
	{
		AtlTrace("%s = %s\n", (*it).second.name.c_str(), (*it).second.value.c_str());
	}
}

void CMTConnectStreamsParser::Stop()
{
	_workerthread.Shutdown(2000);
	m_pSchemaCache=NULL;
	m_pXSDDoc=NULL;
	m_pXMLDoc=NULL;
	::CoUninitialize();
	ReleaseMutex( _hJoinMutex );
}

bool CMTConnectStreamsParser::Join(int nWait)
{
	if( WaitForSingleObject( _hJoinMutex, nWait) == WAIT_OBJECT_0)
		return 1;
	return 0;
}
void CMTConnectStreamsParser::Clear()
{
	_bClear=true;

}
void CMTConnectStreamsParser::Start()
{
	_bInitialized=false;
	_workerthread.AddTimer(
		1000,
		this,
		NULL,
		&_hTimer  // stored newly created timer handle
		) ;
}
void CMTConnectStreamsParser::Initialize()
{
	::CoInitialize(NULL);
	// Setup when we are done with this thread
	static int _nMutexes=0;
	std::string mutexname = StdStringFormat("COpcAdapter JoinMutex %d", _nMutexes++);
	_hJoinMutex.Attach( CreateMutex( NULL, TRUE, mutexname.c_str() ));  
	_bInitialized=true;
}

HRESULT CMTConnectStreamsParser::CloseHandle(HANDLE h)
{
	::CloseHandle(h);  // timer Handle, not CHandle
	return S_OK;
}
void CMTConnectStreamsParser::AddMTConnectDevice(std::string url)
{
	mappeddata[url]=StreamDataDictionary();
}
void CMTConnectStreamsParser::AddNotification(std::string url, FcnDataNotify fcn)
{
	listeners[url].push_back(fcn);
}

void CMTConnectStreamsParser::RemoveMTConnectDevice(std::string url)
{
	try{
		std::map<std::string, StreamDataDictionary>::iterator it = mappeddata.find(url);
		if(it!= mappeddata.end())
		{
			mappeddata.erase(it);
			if(listeners.find(url)!=listeners.end())
				listeners.erase(listeners.find(url));
		}
	}
	catch(...) {}
}

HRESULT CMTConnectStreamsParser::Execute(DWORD_PTR dwParam, HANDLE hObject)
{
	USES_CONVERSION;
	HRESULT hr=S_OK;
	ULONG dwInterval = dwSamplingInterval;
	try 
	{
		CancelWaitableTimer(_hTimer);
		DWORD starttick = GetTickCount();

		if(!_bInitialized)
			Initialize();
		for(std::map<std::string,StreamDataDictionary>::iterator it=mappeddata.begin();
			it!=mappeddata.end(); it++)
		{
			ReadStream((*it).first, (*it).second, dwSamplingInterval);
			std::vector<FcnDataNotify> notifylist = listeners[(*it).first];
			for(int i=0; i< notifylist.size(); i++)
				notifylist[i]((*it).second);
		}
		// Now notify all listeners...

		// Update sleep interval to be more exacting...
#define TICKS_DIFF(cur, prev) ((cur) >= (prev)) ? ((cur)-(prev)) : ((0xFFFFFFFF-(prev))+(cur))
		dwInterval-= TICKS_DIFF(GetTickCount() , starttick);
	}
	catch(...)
	{
		//GLogger<< LDEBUG << "Exception in " << _device << " - CMTConnectStreamsParser::Execute() " << std::endl;;
		hr= E_FAIL;
	}
	if(	_bClear==true)
	{
		mappeddata.clear();
		listeners.clear();
	}
	LARGE_INTEGER liDueTime;
	liDueTime.QuadPart = -10000 * (__int64) ((dwInterval>10000) ? 1000 : dwInterval) ; 
	BOOL bRet = SetWaitableTimer(_hTimer, &liDueTime, 0,  NULL, NULL, FALSE);
	return hr;
}
