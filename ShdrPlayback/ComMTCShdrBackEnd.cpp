//
// ComMTCShdrBackEnd.cpp : Implementation of CComMTCShdrBackEnd
//

// This software was developed by U.S. Government employees as part of
// their official duties and is not subject to copyright. No warranty implied 
// or intended.


#include "stdafx.h"
#include "ComMTCShdrBackEnd.h"
#include "comutil.h"

//#include "Misc.h"
#include "Logger.h"
#include "StdStringFcn.h"
#include <ctime>

#define LOGGER (*gLogger)

#pragma comment(lib, "wininet")
#pragma comment(lib, "comsuppwd.lib")

/**

Todo:
parse timestamp and shdr data (cond?)
read line, wait timestamp amount, output values (assume all samples, events)
read devices xml file for tags types of tags or hand code in ini file :(
or just use msxml and query path to find names and equivalent ids, and types

*/


// CComMTCShdrBackEnd

static bool bRunning=true;
static int nCount=0;
CComMTCShdrBackEnd::CComMTCShdrBackEnd()
{
	_bInited=false;
	_nHeartbeat=0;
	bRunning=true;
}

const int max_length = 1024;

typedef boost::shared_ptr<tcp::socket> socket_ptr;
typedef boost::tuple<int, std::string > StateValues;

//static std::string GetTimeStamp()
//{
//	using namespace boost::posix_time;
//	using namespace boost::gregorian;
//	time_facet * facet = new time_facet("%Y-%m-%dT%H:%M:%S.%F");
//	std::stringstream utc_ss; 
//	utc_ss.imbue(std::locale(std::locale::classic(), facet)); 
//	ptime now = second_clock::local_time();
//	utc_ss << now;
//	return utc_ss.str();
//}

enum TimeFormat
{
  HUM_READ,
  GMT,
  GMT_UV_SEC,
  LOCAL
};
static std::string GetTimeStamp(TimeFormat format=GMT_UV_SEC)
{
#ifdef WIN32
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
#else
  
  
  char timeBuffer[50];
  struct tm * timeinfo;
  struct timeval tv;
  struct timezone tz;

  gettimeofday(&tv, &tz);
  timeinfo = (format == LOCAL) ? localtime(&tv.tv_sec) : gmtime(&tv.tv_sec);
  
  switch (format)
  {
    case HUM_READ:
      strftime(timeBuffer, 50, "%a, %d %b %Y %H:%M:%S %Z", timeinfo);
      break;
    case GMT:
      strftime(timeBuffer, 50, "%Y-%m-%dT%H:%M:%SZ", timeinfo);
      break;
    case GMT_UV_SEC:
      strftime(timeBuffer, 50, "%Y-%m-%dT%H:%M:%S", timeinfo);
      break;
    case LOCAL:
      strftime(timeBuffer, 50, "%Y-%m-%dT%H:%M:%S%z", timeinfo);
      break;
  }
  
  
  if (format == GMT_UV_SEC)
  {
    sprintf(timeBuffer + strlen(timeBuffer), ".%06dZ", tv.tv_usec);
  }
  
  return string(timeBuffer);
#endif
}

// [5244] 2011-06-09T17:50:08.0651|alarm|ESTOP|ESTOP|CRITICAL|ACTIVE|ESTOP Pressed
// 2011-06-09T17:50:12.0588|line|5|heartbeat|6
std::string CComMTCShdrBackEnd::ShdrString(MapValues  values)
{
	std::string szShdrString;
	std::vector<std::string> strs;
	for(MapValueIterator it= values.begin(); it!=values.end(); it++)
	{
		if((*it).second.size() > 0)
		{
			std::string item = (*it).first;
			std::string alias = _ids[item];
			if(alias.size() > 0)
				item=alias;

			//2009-06-15T00:02:19.575164|htemp|WARNING|HTEMP|1|HIGH|Oil Temperature High
			//|condition|FAULT|CONDITION|1|ON|Axis at working area limit
			if(_types[(*it).first]=="condition")
			{
				if(szShdrString.size() > 0)
					strs.push_back(szShdrString);
				szShdrString.clear();
				std::vector<std::string> tokens = TrimmedTokenize((*it).second,".");
				if(tokens.size() < 1)
					continue;
				szShdrString+= "|" + item + "|" + tokens[0] + "|" ;
				if(tokens.size() > 1) szShdrString+= tokens[1];
				szShdrString+= "|";
				if(tokens.size() > 2) szShdrString+= tokens[2];
				szShdrString+= "|";
				if(tokens.size() > 3) szShdrString+= tokens[3];
				szShdrString+= "|";
				if(tokens.size() > 4) szShdrString+= tokens[4];
				// Now push new shdr 
				strs.push_back(szShdrString);
				szShdrString.clear();

			}
			else{
				szShdrString+= "|" + item + "|" + (*it).second;
			}
		}
	}
	if(szShdrString.size() > 0)
	{
		strs.push_back(szShdrString);
	}
	szShdrString.clear();

	for(int i=0; i< strs.size(); i++)
	{
		strs[i]=GetTimeStamp()+ strs[i]+"\n";
		szShdrString+=strs[i];
	}

	return szShdrString;
}

static int ReadLine(socket_ptr sock, std::string &tmp)
{
	boost::system::error_code ec;
	boost::asio::streambuf response;

	try {
		SOCKET native_sock = sock->native();
		int result = SOCKET_ERROR;

		if (INVALID_SOCKET != native_sock)
		{
			DWORD tv=2000;
			result = setsockopt(native_sock, SOL_SOCKET, SO_RCVTIMEO, (char *) &tv,sizeof(DWORD) );
			// result should be zero
		}
		size_t len = boost::asio::read_until(*sock, response, "\n", ec);
		if(len==0)
			return -1;

		if(ec)
			throw boost::system::system_error(ec); // 
		if (ec == boost::asio::error::eof)
			throw boost::system::system_error(ec); // 

		std::istream response_stream(&response);
		getline(response_stream, tmp);
	}
	catch(std::exception & e) 
	{ 
		std::cout<< "ReadLine  Exception " << e.what() << "\n";
		return -1;
	}
	return tmp.size();
}

std::string  CComMTCShdrBackEnd::UpdatedShdrString(MapValues  &localvalues)
{
	std::string info;
	MapValues changedvalues;
	for(MapValueIterator it= _values.begin(); it!=_values.end(); it++)
	{	
		std::string id= (*it).first;
		if(_values[id]!=localvalues[id])
		{
			changedvalues[id]=_values[id];				
		}
	}
	//changedvalues["heartbeat"]=StdStringFormat("%d", _nHeartbeat++);

	info = ShdrString(changedvalues);
	return info;

}
static void trans_func( unsigned int u, EXCEPTION_POINTERS* pExp )
{
	OutputDebugString( StdStringFormat("PcDmisAdapter trans_func - Code = 0x%x\n",  
		pExp->ExceptionRecord->ExceptionCode).c_str() );
	throw std::exception();
}
void CComMTCShdrBackEnd::session(socket_ptr sock)
{
	try
	{
		_set_se_translator( trans_func );  // correct thread?
		// first entry write out all of the information...
		// then loop every second or so spitting out any newest information.
		MapValues                 localvalues;

		std::string info = ShdrString(_values);
		boost::asio::write(*sock, boost::asio::buffer(info.c_str(), info.size()));
		for (nCount++;bRunning;)
		{
			localvalues=_values;
			boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
			boost::system::error_code ec;

			boost::system::error_code error;
			std::string tmp;

			int n = ReadLine(sock, tmp); // n>=0 data...
			if (strncmp(tmp.c_str(), "* PING", 6) == 0)
			{
				int aHeartbeatFreq = 10000;
				std::string mPong= StdStringFormat( "* PONG %d\n", aHeartbeatFreq);
				boost::asio::write(*sock, boost::asio::buffer(mPong.c_str(), mPong.size()));
			}
			std::cout<< "Received: " << tmp << std::endl;

			MapValues changedvalues;
			for(MapValueIterator it= _values.begin(); it!=_values.end(); it++)
			{	
				std::string id= (*it).first;
				if(_values[id]!=localvalues[id])
				{
					changedvalues[id]=_values[id];				
				}
			} 
			//changedvalues["heartbeat"]=StdStringFormat("%d", _nHeartbeat++);

			info = ShdrString(changedvalues);
			if(info.size() < 1)
				continue;
			boost::asio::write(*sock, boost::asio::buffer(info.c_str(), info.size()));

			if(ec)
				throw boost::system::system_error(ec); // 
			if (ec == boost::asio::error::eof)
				throw boost::system::system_error(ec); // 	

		}
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception in thread: " << e.what() << "\n";
	}
	catch (...)
	{
		std::cerr << "Exception in thread\n";
	}	
	nCount--;
}

void CComMTCShdrBackEnd::server(boost::asio::io_service& io_service, short port)
{

	try
	{
		m_pAcceptor =  new tcp::acceptor(io_service, tcp::endpoint(tcp::v4(), port)) ;
		m_pAcceptor->set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
		StartAsyncAccept();
		// Thread will stop here...
		_io_service.run();

	}
	catch(...)
	{
		OutputDebugString("Fatal Error in CComMTCShdrBackEnd::server\n");
	}
	//tcp::acceptor a(io_service, tcp::endpoint(tcp::v4(), port));
	//try {
	//	for (;bRunning;)
	//	{
	//		socket_ptr sock(new tcp::socket(io_service));
	//		a.accept(*sock);
	//		boost::thread t(boost::bind(&CComMTCShdrBackEnd::session, this, sock));
	//	}
	//}
	//catch(...)
	//{

	//}
}

void CComMTCShdrBackEnd::StopAsyncAccept()
{
	try{
	m_pAcceptor->cancel();
	}
	catch(boost::system::system_error)
	{

	}
}

void CComMTCShdrBackEnd::StartAsyncAccept()
{
//	tcp_connection::pointer new_connection =
//		tcp_connection::create(m_pAcceptor->io_service());

	pSocket= socket_ptr( new tcp::socket(_io_service));

	m_pAcceptor->async_accept(*pSocket, bind(&CComMTCShdrBackEnd::HandleAsyncAccept, this, boost::asio::placeholders::error));   
}

void CComMTCShdrBackEnd::HandleAsyncAccept(const boost::system::error_code& error) // socket_ptr pSocket)
{
	if(bRunning)
	{
		boost::thread t(boost::bind(&CComMTCShdrBackEnd::session, this, pSocket));
		if(bRunning)
			StartAsyncAccept();
	}
}
STDMETHODIMP CComMTCShdrBackEnd::StoreValue(BSTR bstrDataItemName, BSTR bstrvalue, std::string type, BSTR bstrNativeCode, BSTR bstrSeverity , BSTR bstrQualifier, BSTR bstrText)
{
	USES_CONVERSION;
	HRESULT hr=S_OK;
	std::string dataItemName=W2A(bstrDataItemName);
	std::string value=W2A(bstrvalue);
	std::string nativeCode=W2A(bstrNativeCode);
	std::string qualifier=W2A(bstrQualifier);
	std::string severity=W2A(bstrSeverity);
	std::string text=W2A(bstrText);
	try 
	{
		// Check for bogus id
		if(_ids.find(dataItemName) == _ids.end())
			return E_INVALIDARG;  // fail but CNC may not have this tag

		std::string id= _ids[dataItemName];
		if(id.empty())
			return E_FAIL;
		if(_types[dataItemName]=="condition")
		{
			//	2009-06-15T00:02:19.575164|htemp|WARNING|HTEMP|1|HIGH|Oil Temperature High
			//text, mNativeCode, mNativeSeverity,mQualifier
			value=value + "." + nativeCode + "." + severity  + "." + qualifier + "."+ text;
		}
		_values[dataItemName]=value;

	}
	catch(std::string errmsg)
	{
		Logger.Warning((LPCTSTR) errmsg.c_str());
	}
	return hr;
}
STDMETHODIMP CComMTCShdrBackEnd::Init(BSTR domain, LONG portnumber, BSTR devicename)
{
	USES_CONVERSION;
	_bInited=true;
	_domainname=W2A(domain);
	_portnumber=portnumber;
	_deviceName=W2A(devicename);
	//server(io_service, 7878);
	boost::thread t(boost::bind(&CComMTCShdrBackEnd::server, this, boost::ref( _io_service), portnumber)); 
	return S_OK;
}
STDMETHODIMP CComMTCShdrBackEnd::PowerOnConnection(void)
{
	// FIXME: determine difference
	StoreValue(_bstr_t("power"), _bstr_t("ON"), EVENT, _bstr_t(""), _bstr_t(""));
	return StoreValue(_bstr_t("available"), _bstr_t("AVAILABLE"), EVENT, _bstr_t(""), _bstr_t(""));
}
STDMETHODIMP CComMTCShdrBackEnd::PowerOffConnection(void)
{
	StoreValue(_bstr_t("power"), _bstr_t("OFF"), EVENT, _bstr_t(""), _bstr_t(""));
	return StoreValue(_bstr_t("available"), _bstr_t("UNAVAILABLE"), EVENT, _bstr_t(""), _bstr_t(""));
}

STDMETHODIMP CComMTCShdrBackEnd::StoreTagMap(BSTR map)
{
	USES_CONVERSION;
	_ids=ParseIniString(W2A(map));
	return S_OK;
}

STDMETHODIMP CComMTCShdrBackEnd::StoreTypeMap(BSTR csvIds,BSTR csvTypes)
{
	USES_CONVERSION;
	std::string ids = W2A( csvIds);
	std::string types = W2A( csvTypes);
	
	std::vector<std::string> idlist = TrimmedTokenize(ids,",");
	std::vector<std::string> typelist = TrimmedTokenize(types,",");
	if(idlist.size()!=typelist.size())
		return E_INVALIDARG;

	for(int i=0; i< idlist.size(); i++)
		_types[idlist[i]]= typelist[i];

	return S_OK;
}
STDMETHODIMP CComMTCShdrBackEnd::Quit()
{
	StopAsyncAccept();
	bRunning=false;
	for(int i=0; i< 5 && nCount; i++)
		boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
	//_io_service.stop();

	return S_OK;
}
STDMETHODIMP CComMTCShdrBackEnd::GetTagValues(BSTR * values)
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
