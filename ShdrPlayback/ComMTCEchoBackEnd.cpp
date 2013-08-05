// ComMTCEchoBackEnd.cpp : Implementation of CComMTCEchoBackEnd

#include "stdafx.h"
#include "ComMTCEchoBackEnd.h"
#include "Logger.h"
#include "StdStringFcn.h"
#include "comutil.h"

#pragma comment(lib, "comsuppwd.lib")

typedef boost::tuple<int, std::string > StateValues;
static bool bRunning=true;
static int nCount=0;

static std::string GetTimeStamp()
{
	using namespace boost::posix_time;
	using namespace boost::gregorian;
	time_facet * facet = new time_facet("%Y-%m-%dT%H:%M:%S.%F");
	std::stringstream utc_ss; 
	utc_ss.imbue(std::locale(std::locale::classic(), facet)); 
	ptime now = second_clock::local_time();
	utc_ss << now;
	return utc_ss.str();
}

// CComMTCEchoBackEnd

CComMTCEchoBackEnd::CComMTCEchoBackEnd()
{
	_ids["available"]="id1";
	_ids["Srpm"]="id3";
	_ids["execution"]="id11";
	_ids["mode"] = "id12";
	_ids["block"] = "id10";
	_ids["program"] = "id13";
	_ids["Xabs"]= "id4";
	_ids["Yabs"]= "id6";
	_ids["Zabs"]= "id8";
	_ids["line"]= "id14";
	_ids["path_feedratefrt"]= "id2";
	_nHeartbeat=0;
}
// [5244] 2011-06-09T17:50:08.0651|alarm|ESTOP|ESTOP|CRITICAL|ACTIVE|ESTOP Pressed
// 2011-06-09T17:50:12.0588|line|5|heartbeat|6
std::string CComMTCEchoBackEnd::ShdrString(MapValues  values)
{
	std::string szShdrString;
	for(MapValueIterator it= values.begin(); it!=values.end(); it++)
	{
		if((*it).second.size() > 0)
		{
			std::string item = (*it).first;
			std::string alias = _ids[item];
			if(alias.size() > 0)
				item=alias;

			szShdrString+= "|" + item + "|" + (*it).second;
		}
		
	}
	if(szShdrString.size() > 0)
	{
		szShdrString=GetTimeStamp()+ szShdrString+"\n";
	}
	return szShdrString;
}

void CComMTCEchoBackEnd::session( )
{
	try
	{
		// first entry write out all of the information...
		// then loop every second or so spitting out any newest information.
		MapValues                 localvalues;

		std::string info = ShdrString(_values);
		if(_OutputFile.good())
			_OutputFile<<info;
		for (nCount++;bRunning;)
		{
			localvalues=_values;
			boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
			boost::system::error_code ec;

			boost::system::error_code error;
			std::string tmp;

			MapValues changedvalues;
			for(MapValueIterator it= _values.begin(); it!=_values.end(); it++)
			{	
				std::string id= (*it).first;
				if(_values[id]!=localvalues[id])
				{
					changedvalues[id]=_values[id];				
				}
			}
			changedvalues["heartbeat"]=StdStringFormat("%d", _nHeartbeat++);
			info = ShdrString(changedvalues);
//			boost::asio::write(*sock, boost::asio::buffer(info.c_str(), info.size()));
			if(_OutputFile.good())
				_OutputFile<<info;


		}
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception in thread: " << e.what() << "\n";
	}
	nCount--;
}


STDMETHODIMP CComMTCEchoBackEnd::StoreValue(BSTR bstrDataItemName, BSTR bstrvalue, STORETYPE type, BSTR bstrAlarmCode, BSTR bstrAlarmNative)
{
	USES_CONVERSION;
	HRESULT hr=S_OK;
	std::string dataItemName=W2A(bstrDataItemName);
	std::string value=W2A(bstrvalue);
	std::string alarm_code=W2A(bstrAlarmCode);
	std::string alarm_nativecode=W2A(bstrAlarmNative);
	try {
	// Check for bogus id
	if(_ids.find(dataItemName) == _ids.end())
		return E_INVALIDARG;  // fail but CNC may not have this tag

	std::string id= _ids[dataItemName];
	if(id.empty())
		return E_FAIL;
	// FIXME: if conditiono add extra shdr stuff
	_values[dataItemName]=value;

	}
	catch(std::string errmsg)
	{
		Logger.Warning((LPCTSTR) errmsg.c_str());
	}
	return hr;
}
STDMETHODIMP CComMTCEchoBackEnd::Init(BSTR domain, LONG portnumber, BSTR devicename)
{
	USES_CONVERSION;
	_bInited=true;
	_domainname=W2A(domain);
	_portnumber=portnumber;
	_deviceName=W2A(devicename);

	_filename=::ExeDirectory()+_deviceName + ".txt";
	_OutputFile.open(_filename.c_str(), std::fstream::out, OF_SHARE_DENY_NONE);
	if(!_OutputFile.good())
	{
		OutputDebugString("CComMTCEchoBackEnd file open failed\n");
		return E_FAIL;
	}
	else
		boost::thread t(boost::bind(&CComMTCEchoBackEnd::session, this)); 
	return S_OK;
}
STDMETHODIMP CComMTCEchoBackEnd::PowerOnConnection(void)
{
	// FIXME: determine difference
	StoreValue(_bstr_t("power"), _bstr_t("ON"), EVENT, _bstr_t(""), _bstr_t(""));
	return StoreValue(_bstr_t("available"), _bstr_t("AVAILABLE"), EVENT, _bstr_t(""), _bstr_t(""));
}
STDMETHODIMP CComMTCEchoBackEnd::PowerOffConnection(void)
{
	StoreValue(_bstr_t("power"), _bstr_t("OFF"), EVENT, _bstr_t(""), _bstr_t(""));
	return StoreValue(_bstr_t("available"), _bstr_t("UNAVAILABLE"), EVENT, _bstr_t(""), _bstr_t(""));
}
STDMETHODIMP CComMTCEchoBackEnd::StoreTagMap(BSTR map)
{
	USES_CONVERSION;
	_ids=ParseIniString(W2A(map));
	return S_OK;
}
STDMETHODIMP CComMTCEchoBackEnd::Quit()
{
	bRunning=false;
	boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
	return S_OK;
}
STDMETHODIMP CComMTCEchoBackEnd::GetTagValues(BSTR * values)
{
	std::string str;
	for(MapValueIterator it = _values.begin();it != _values.end(); it++)
	{
		str+=	 (*it).first + "=" +  (*it).second + "\n";
	}
	_bstr_t bstr = (LPCSTR) str.c_str();
	*values=bstr.Detach();
	return S_OK;
}