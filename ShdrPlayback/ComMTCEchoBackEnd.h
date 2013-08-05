// ComMTCEchoBackEnd.h : Declaration of the CComMTCEchoBackEnd
//
#pragma once
#include "resource.h"       // main symbols
#pragma comment(lib, "comsuppwd.lib")



#include "MTCShdrBackEnd_i.h"

#include <map>
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>

#include <boost/bind.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/tuple/tuple.hpp>
#include "boost/date_time/posix_time/posix_time.hpp"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CComMTCEchoBackEnd

class ATL_NO_VTABLE CComMTCEchoBackEnd :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CComMTCEchoBackEnd, &CLSID_ComMTCEchoBackEnd>,
	public IDispatchImpl<IComMTCBackEnd, &IID_IComMTCBackEnd, &LIBID_MTCEchoBackEndLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	typedef boost::tuple<STORETYPE, std::string > StateValues;
	typedef std::map<std::string, std::string> MapValues;
	typedef MapValues::iterator MapValueIterator;

	CComMTCEchoBackEnd();



BEGIN_COM_MAP(CComMTCEchoBackEnd)
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
	std::string					ShdrString(MapValues  values);
	void						session();

	MapValues                 _ids;
	MapValues                 _values;
	bool                      _bInited;
	int                       _portnumber;
	std::string              _domainname;
	std::string              _deviceName;
	bool	                 _bLastConnected;
	UINT					_nHeartbeat;	
	std::fstream			_OutputFile;
	std::string				_filename;
public:

	STDMETHOD(StoreValue)(BSTR dataItemName, BSTR value, STORETYPE type, BSTR alarm_code, BSTR alarm_native);
	STDMETHOD(Init)(BSTR domain, LONG portnumber, BSTR devicename);
	STDMETHOD(PowerOnConnection)(void);
	STDMETHOD(PowerOffConnection)(void);
	STDMETHOD(StoreTagMap)(BSTR map);
	STDMETHOD(Quit)(void);
	STDMETHOD(GetTagValues)(BSTR * values);

};
typedef CComObject<CComMTCEchoBackEnd> CoComMTCEchoBackEnd;
//OBJECT_ENTRY_AUTO(__uuidof(ComMTCEchoBackEnd), CComMTCEchoBackEnd)
