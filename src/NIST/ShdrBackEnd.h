//
// ComMTCShdrBackEnd.h : Declaration of the CComMTCShdrBackEnd
//

// This software was developed by U.S. Government employees as part of
// their official duties and is not subject to copyright. No warranty implied 
// or intended.

#pragma once
#include "resource.h"       // main symbols

#include <map>
#include <cstdlib>
#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/tuple/tuple.hpp>
#include "boost/date_time/posix_time/posix_time.hpp"
#include <boost/shared_ptr.hpp>

#include "MTConnectDeviceParser.h"
#include "Logger.h"

using boost::asio::ip::tcp;
typedef boost::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr;


using namespace ATL;

typedef std::map<std::string, std::string> MapValues;
typedef MapValues::iterator MapValueIterator;

/** Todo

1) configure timing of shdr backend, default updates every second
2) gracefull shutdown of threads
*/

class  CShdrBackEnd 
{
public:
	typedef std::map<std::string, std::string> MapValues;
	typedef std::map<std::string, std::string> MapTypes;
	typedef MapValues::iterator MapValueIterator;

	CShdrBackEnd();
	CLogger & MyLogger()				{ return _logger;}
	std::string & DevicesXmlFilename()	{ return _devicesxmlfilename; }
	UINT & IpPort()						{ return _ipport; }
	std::string & DeviceName()			{ return _devicename; }
	MTConnectDataModel  GetDataItems()	{ return _dataItems; }

	void							session(socket_ptr sock);
	void							server(boost::asio::io_service& io_service, short port);
	void							HandleAsyncAccept(const boost::system::error_code& error);
	void							StartAsyncAccept();
	void							StopAsyncAccept();

	void Init(std::string devicesxmlfilename, 
		int ipport, 
		std::string devicename);
	std::string						UpdatedShdrString(MapValues  &localvalues);
	std::string						ShdrString(MapValues  values);

	bool  GetDataItem(std::string d, CDataItem & dataItem);
	std::string GetType(std::string d)	{ return _dataItems[d].type; }
	std::string GetCategory(std::string d)	{ return _dataItems[d].category; }
	bool IsValidId(std::string d)	{ return _dataItems.find(d) != _dataItems.end() ; }
	std::string GetAlias(std::string s)	{ return s; }

	STDMETHOD(StoreValue)(std::string dataItemName, std::string value, std::string type, std::string nativeCode="", std::string severity="", std::string qualifier="", std::string text="");
	STDMETHOD(PowerOnConnection)(void);
	STDMETHOD(PowerOffConnection)(void);
	STDMETHOD(Quit)(void);

	MapValues						_aliases;
	MapValues						_values;
	MapValues						localvalues;

	bool							_bInited;
	UINT							_nHeartbeat;
	CLogger							_logger;

	// Shdr socket service
	boost::asio::io_service			_io_service;
	tcp::acceptor *					m_pAcceptor;
	socket_ptr						pSocket;

	// Shdr parameters - device name, port, devices.xml filename
	std::string						_devicesxmlfilename;
	std::string						_devicename;
	UINT							_ipport;

	// Device parser, and parsed dataitems
	MTConnectDeviceParser			_deviceparser;
	MTConnectDataModel				 _dataItems;

	//Heartbeat thread to update heartbeat event
	boost::mutex					io_mutex;
	boost::thread					_heartbeatthread;
	void							Heartbeat();
	void							JoinHeartbeat() { _heartbeatthread.join(); }
	void							StopHeartbeat() { _heartbeatthread.interrupt(); }
	void							StartHeartbeat() {_heartbeatthread= boost::thread(boost::bind(&CShdrBackEnd::Heartbeat, this)); }
	
};
