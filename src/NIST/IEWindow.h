//
// IEWindow.h
//

#pragma once


#define INITGUID
#include <initguid.h>
#include <memory.h>
#include <comdef.h>
#include "atlstr.h"
#include <mshtml.h>
#include <exdisp.h>
#include <exdispid.h>
//#include "webbrowser2.h"
#include "atliface.h"
#include <string>
#include  <mshtmdid.h>
#include <vector>
#include "MTConnectStreamsParser.h"

#define DISPID_COMMANDSTATECHANGE 105

//__declspec(selectany) _ATL_FUNC_INFO BeforeNavigate2Info =
//{ CC_STDCALL, VT_EMPTY, 7,
//{ VT_DISPATCH, VT_VARIANT|VT_BYREF, VT_VARIANT|VT_BYREF, 
//VT_VARIANT|VT_BYREF, VT_VARIANT|VT_BYREF, VT_VARIANT|VT_BYREF, 
//VT_BOOL|VT_BYREF }
//};
//
//__declspec(selectany) _ATL_FUNC_INFO CommandStateChangeInfo =
//{ CC_STDCALL, VT_EMPTY, 2, { VT_I4, VT_BOOL }
//};


class CIEWindow 
//	: public IDispEventImpl<37, CIEWindow, &DIID_DWebBrowserEvents2, &LIBID_SHDocVw, 1, 1> 

{
public:
	CIEWindow(void);
	~CIEWindow(void);

	void OpenIE();
	void CloseIE();
	bool IsAlive();
	HRESULT GetBody();
	HRESULT SetDocumentText( std::string cstr);
	HRESULT SetElementId(std::string id, std::string str);
	HRESULT SetWindowTitle(std::string s);
	void SaveSnapshot(std::string snapshot) 
	{ 
		if(_lastsnapshot==snapshot)
			return;
		_lastsnapshot=snapshot;
		_snapshots.push_back(snapshot); 
	}
	void LoadFields(std::string fields);

	int SetSnapshot(int i=-1);
	void StoreSnapshot(std::string snapshot);

	CComPtr<IHTMLElement> GetElement(const TCHAR *id);

	CComPtr<IWebBrowser2> m_spWebBrowser;
	CComPtr<IHTMLElement> m_pBody;
	CComPtr<IHTMLDocument2> m_spHTMLDocument;
	std::string _lastsnapshot;
	std::vector<std::string> _snapshots ;
	unsigned int _nSnapshot;
	int _nLive;

	//BEGIN_SINK_MAP(CIEWindow)
 //       SINK_ENTRY_INFO(37, DIID_DWebBrowserEvents2, DISPID_BEFORENAVIGATE2, OnBeforeNavigate, &BeforeNavigate2Info)     
	//END_SINK_MAP()
	std::string  CreateHtmlTable(std::vector<DataDictionary> datum);
	std::string  CreateHtmlRow(DataDictionary data);
	void __stdcall OnBeforeNavigate(IDispatch *pDisp,VARIANT *URL,
		VARIANT *Flags,VARIANT *TargetFrameName,VARIANT *PostData,VARIANT *Headers,
		VARIANT_BOOL *Cancel);

	// Configuration
	std::vector<std::string> _fields;
	static std::string numberfields;
	std::map<std::string, std::string> _valuerenames;
	std::map<std::string, std::string> _colormapping;
	std::map<std::string, std::string> _formats;

};
