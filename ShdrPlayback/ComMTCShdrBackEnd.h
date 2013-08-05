//
// ComMTCShdrBackEnd.h : Declaration of the CComMTCShdrBackEnd
//

// This software was developed by U.S. Government employees as part of
// their official duties and is not subject to copyright. No warranty implied 
// or intended.

#pragma once
#include "resource.h"       // main symbols
#include "MTCShdrBackEnd_i.h"

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

#include "Logger.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif


using boost::asio::ip::tcp;
typedef boost::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr;


using namespace ATL;

typedef std::map<std::string, std::string> MapValues;
typedef MapValues::iterator MapValueIterator;
// CComMTCShdrBackEnd

class ATL_NO_VTABLE CComMTCShdrBackEnd :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CComMTCShdrBackEnd, &CLSID_ComMTCShdrBackEnd>,
	public IDispatchImpl<IComMTCBackEnd, &IID_IComMTCBackEnd, &LIBID_MTCShdrBackEndLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	typedef boost::tuple<STORETYPE, std::string > StateValues;
	typedef std::map<std::string, std::string> MapValues;
	typedef std::map<std::string, std::string> MapTypes;
	typedef MapValues::iterator MapValueIterator;

	CComMTCShdrBackEnd();


	//DECLARE_REGISTRY_RESOURCEID(IDR_COMMTCSHDRBACKEND)


	BEGIN_COM_MAP(CComMTCShdrBackEnd)
		COM_INTERFACE_ENTRY(IComMTCBackEnd)
		COM_INTERFACE_ENTRY(IDispatch)
	END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}
	CLogger & MyLogger() { return _logger;}

	boost::asio::io_service		_io_service;
	tcp::acceptor *				m_pAcceptor;
	socket_ptr pSocket;
	void						session(socket_ptr sock);
	void						server(boost::asio::io_service& io_service, short port);
	void						HandleAsyncAccept(const boost::system::error_code& error);
	void						StartAsyncAccept();
	void						StopAsyncAccept();
	std::string					UpdatedShdrString(MapValues  &localvalues);
	std::string					ShdrString(MapValues  values);

	MapValues                 _ids;
	MapTypes                  _types;
	MapValues                 _values;
	bool                      _bInited;
	int                       _portnumber;
	std::string              _domainname;
	std::string              _deviceName;
	bool	                 _bLastConnected;
	UINT					_nHeartbeat;
	CLogger                  _logger;

public:

	// Condition
	//ELevels     eUNAVAILABLE,    eNORMAL,    eWARNING,    eFAULT
	// the Condition already has a name
	// Text is the <FAULT>text</FAULT>
    //bool setValue(ELevels aLevel, const char *aText = "", const char *aCode = "",
	//const char *aQualifier = "", const char *aSeverity = "");
	//

	STDMETHOD(StoreValue)(BSTR dataItemName, BSTR value, STORETYPE type, BSTR alarm_code, BSTR alarm_native){ return E_NOTIMPL; }
	STDMETHOD(StoreValue)(BSTR dataItemName, BSTR value, std::string code, BSTR bstrNativeCode=L"", BSTR bstrSeverity=L"" , BSTR bstrQualifier=L"", BSTR bstrText=L"");
	STDMETHOD(Init)(BSTR domain, LONG portnumber, BSTR devicename);
	STDMETHOD(PowerOnConnection)(void);
	STDMETHOD(PowerOffConnection)(void);
	STDMETHOD(StoreTagMap)(BSTR map);
	STDMETHOD(StoreTypeMap)(BSTR map, BSTR types);
	STDMETHOD(Quit)(void);
	STDMETHOD(GetTagValues)(BSTR * values);
};

typedef CComObject<CComMTCShdrBackEnd> CoComMTCShdrBackEnd;
//OBJECT_ENTRY_AUTO(__uuidof(ComMTCShdrBackEnd), CComMTCShdrBackEnd)
