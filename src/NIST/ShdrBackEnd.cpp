//
// ComMTCShdrBackEnd.cpp : Implementation of CShdrBackEnd
//

// This software was developed by U.S. Government employees as part of
// their official duties and is not subject to copyright. No warranty implied 
// or intended.


#include "stdafx.h"
#include "ShdrBackEnd.h"
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


// CShdrBackEnd

static bool bRunning=true;
static int nCount=0;
CShdrBackEnd::CShdrBackEnd()
{
	_bInited=false;
	_nHeartbeat=0;
	bRunning=true;
}




const int max_length = 1024;

typedef boost::shared_ptr<tcp::socket> socket_ptr;

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
std::string CShdrBackEnd::ShdrString(MapValues  values)
{
	std::string szShdrString;
	std::vector<std::string> strs;
	for(MapValueIterator it= values.begin(); it!=values.end(); it++)
	{
		if((*it).second.size() > 0)
		{
			std::string item = (*it).first;
			std::string alias = _aliases[item];
			if(alias.size() > 0)
				item=alias;

			//2009-06-15T00:02:19.575164|htemp|WARNING|HTEMP|1|HIGH|Oil Temperature High
			//|condition|FAULT|CONDITION|1|ON|Axis at working area limit
			if(GetCategory((*it).first)=="condition")
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
			else if(GetCategory((*it).first)=="asset_changed") 
			{

				szShdrString+= "|" + item + "|" + ExtractFilename((*it).second) ;
				if(szShdrString.size() > 0)
					strs.push_back(szShdrString);
				std::string contents;
				ReadFile((*it).second, contents);
				szShdrString.clear();
				szShdrString+="|@ASSET@|";
				szShdrString+=item;
				szShdrString+="|";
				szShdrString+="PartProgram"; // aType;
				szShdrString+="|--multiline--ABCD\n";
				szShdrString+=contents;
				szShdrString+="\n--multiline--ABCD";

				if(szShdrString.size() > 0)
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
bool  CShdrBackEnd::GetDataItem(std::string d, CDataItem & dataItem) 
	{ 
		if(_dataItems.find(d) == _dataItems.end())
			return false;
		dataItem= _dataItems[d]; 
		return true;
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

std::string  CShdrBackEnd::UpdatedShdrString(MapValues  &localvalues)
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
void CShdrBackEnd::session(socket_ptr sock)
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

void CShdrBackEnd::server(boost::asio::io_service& io_service, short port)
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
		OutputDebugString("Fatal Error in CShdrBackEnd::server\n");
	}
	//tcp::acceptor a(io_service, tcp::endpoint(tcp::v4(), port));
	//try {
	//	for (;bRunning;)
	//	{
	//		socket_ptr sock(new tcp::socket(io_service));
	//		a.accept(*sock);
	//		boost::thread t(boost::bind(&CShdrBackEnd::session, this, sock));
	//	}
	//}
	//catch(...)
	//{

	//}
}

void CShdrBackEnd::StopAsyncAccept()
{
	try{
		m_pAcceptor->cancel();
	}
	catch(boost::system::system_error)
	{

	}
}

void CShdrBackEnd::StartAsyncAccept()
{
	//	tcp_connection::pointer new_connection =
	//		tcp_connection::create(m_pAcceptor->io_service());

	pSocket= socket_ptr( new tcp::socket(_io_service));

	m_pAcceptor->async_accept(*pSocket, bind(&CShdrBackEnd::HandleAsyncAccept, this, boost::asio::placeholders::error));   
}

void CShdrBackEnd::HandleAsyncAccept(const boost::system::error_code& error) // socket_ptr pSocket)
{
	if(bRunning)
	{
		boost::thread t(boost::bind(&CShdrBackEnd::session, this, pSocket));
		if(bRunning)
			StartAsyncAccept();
	}
}
STDMETHODIMP CShdrBackEnd::StoreValue(std::string dataItemName, std::string value, std::string type, std::string nativeCode, std::string severity , std::string qualifier, std::string text)
{
	HRESULT hr=S_OK;
	try 
	{
		boost::mutex::scoped_lock  lock(io_mutex);
		// Check for bogus id
		if(!IsValidId(dataItemName))
			return E_INVALIDARG;  // fail but CNC may not have this tag

		std::string id= GetAlias(dataItemName);
		if(id.empty())
			return E_FAIL;
		//	2009-06-15T00:02:19.575164|htemp|WARNING|HTEMP|1|HIGH|Oil Temperature High
		//text, mNativeCode, mNativeSeverity,mQualifier
		if(GetCategory(dataItemName)=="condition")
		{
			value=value + "." + nativeCode + "." + severity  + "." + qualifier + "."+ text;
		}
		_values[dataItemName]=value;

	}
	catch(std::string errmsg)
	{
		GLogger.Warning((LPCTSTR) errmsg.c_str());
	}
	return hr;
}
void CShdrBackEnd::Init(std::string devicesxmlfilename, 
		int ipport, 
		std::string devicename)
{
	USES_CONVERSION;
	_bInited=true;

	DevicesXmlFilename()=devicesxmlfilename;
	IpPort()=ipport;
	DeviceName() = devicename;

	if(DevicesXmlFilename().empty())
		DevicesXmlFilename()=ExeDirectory() + "devices.xml";
	_dataItems = _deviceparser.ReadDeviceDescription(DevicesXmlFilename());

	std::string storemap,itemlist, typelist;
	//server(io_service, 7878);
	boost::thread t(boost::bind(&CShdrBackEnd::server, this, boost::ref( _io_service), IpPort())); 
}
STDMETHODIMP CShdrBackEnd::PowerOnConnection(void)
{
	// FIXME: determine difference
	StoreValue("power", "ON", "event", "", "");
	return StoreValue("available", "AVAILABLE", "event", "", "");
}
STDMETHODIMP CShdrBackEnd::PowerOffConnection(void)
{
	StoreValue("power", "OFF", "event", "", "");
	return StoreValue("available", "UNAVAILABLE", "event", "", "");
}

STDMETHODIMP CShdrBackEnd::Quit()
{
	StopAsyncAccept();
	bRunning=false;
	// FIXME: use join with timeout and then interrupt
	for(int i=0; i< 5 && nCount; i++)
		boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
	//_io_service.stop();

	return S_OK;
}

void CShdrBackEnd::Heartbeat()
{
   int heartbeat =0;
   while(1)
   {
	   try{ 
		   boost::this_thread::sleep(boost::posix_time::milliseconds(1000));  
		   StoreValue("heartbeat", StdStringFormat("%d",heartbeat++), "event");
		   boost::this_thread::interruption_point();
	   }
	   catch(const boost::thread_interrupted&)
	   {
		   // Thread interruption request received, break the loop
		   std::cout<<"- Heartbeat Thread interrupted. Exiting thread."<<std::endl;
		   break;
	   }
   }
}