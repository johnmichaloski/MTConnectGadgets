// WtlHtmlView.h : interface of the CWtlHtmlView class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
#include <mshtml.h>
#include "atlstr.h"
#include <mshtml.h>
#include <exdisp.h>
//#include "webbrowser2.h"
#include "atliface.h"
#include "exdispid.h"
/////////////////////////////////////////////////////////////////////////////
// Info structs used by the event sink map

__declspec(selectany) _ATL_FUNC_INFO BeforeNavigate2Info =
{ CC_STDCALL, VT_EMPTY, 7,
{ VT_DISPATCH, VT_VARIANT|VT_BYREF, VT_VARIANT|VT_BYREF, 
VT_VARIANT|VT_BYREF, VT_VARIANT|VT_BYREF, VT_VARIANT|VT_BYREF, 
VT_BOOL|VT_BYREF }
};

__declspec(selectany) _ATL_FUNC_INFO NavigateComplete2Info =
{ CC_STDCALL, VT_EMPTY, 2, { VT_DISPATCH, VT_VARIANT|VT_BYREF } 
};

__declspec(selectany) _ATL_FUNC_INFO StatusChangeInfo =
{ CC_STDCALL, VT_EMPTY, 1, { VT_BSTR }
};

__declspec(selectany) _ATL_FUNC_INFO CommandStateChangeInfo =
{ CC_STDCALL, VT_EMPTY, 2, { VT_I4, VT_BOOL }
};

__declspec(selectany) _ATL_FUNC_INFO DownloadInfo =
{ CC_STDCALL, VT_EMPTY, 0 
};


class CWtlHtmlView :
	public CWindowImpl<CWtlHtmlView, CAxWindow>,
	public IDispEventSimpleImpl<37, CWtlHtmlView, &DIID_DWebBrowserEvents2>
{
public:
	DECLARE_WND_SUPERCLASS(NULL, CAxWindow::GetWndClassName())


	CComPtr<IHTMLElement> m_pBody;
	CComPtr<IHTMLDocument2> m_spHTMLDocument;
	CComPtr<IWebBrowser2> m_spWebBrowser2;
	CComPtr<IWebBrowser> m_spWebBrowser;
	bool bBackEnable;
	bool bForwardEnable;

	CWtlHtmlView();
	~CWtlHtmlView();
	BOOL PreTranslateMessage(MSG* pMsg);
	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

	BEGIN_MSG_MAP(CWtlHtmlView)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	END_MSG_MAP()

	BOOL GetBody();
	HRESULT SetDocumentText( bstr_t bstr);
	void CWtlHtmlView::Write(LPCTSTR string);
	void CWtlHtmlView::Clear();
	IHTMLDocument2 *CWtlHtmlView::GetDocument();

	HRESULT Navigate(bstr_t url);
	void OnPrintpreview() ;
	void GoBack() ;
	void GoForward() ;
	void Refresh();

	HRESULT OnExecCommand( OLECMDID nCmdID, OLECMDEXECOPT nCmdExecOpt,
   VARIANTARG* pvarargIn=NULL, VARIANTARG* pvarargOut=NULL) ;
	HRESULT ExecCommand( OLECMDID nCmdID, OLECMDEXECOPT nCmdExecOpt, VARIANTARG* pvarargIn, VARIANTARG* pvarargOut) ;
	bool QueryStatus( OLECMDID nCmdID, int value);

	LRESULT TurnOffContextMenu()
	{
		HRESULT hr;
		CAxWindow wnd(m_hWnd);
		CComPtr<IUnknown> spUnk;					
		AtlAxGetHost(m_hWnd, &spUnk);				
		CComQIPtr<IAxWinAmbientDispatch> spWinAmb(spUnk);
		hr=spWinAmb->put_AllowContextMenu(VARIANT_FALSE);
		return SUCCEEDED(hr) ? 0 : -1;
	}

	BEGIN_SINK_MAP(CWtlHtmlView)
		SINK_ENTRY_INFO(37, DIID_DWebBrowserEvents2, DISPID_BEFORENAVIGATE2, OnBeforeNavigate2, &BeforeNavigate2Info)
		SINK_ENTRY_INFO(37, DIID_DWebBrowserEvents2, DISPID_NAVIGATECOMPLETE2, OnNavigateComplete2, &NavigateComplete2Info)
		SINK_ENTRY_INFO(37, DIID_DWebBrowserEvents2, DISPID_STATUSTEXTCHANGE, OnStatusChange, &StatusChangeInfo)
		SINK_ENTRY_INFO(37, DIID_DWebBrowserEvents2, DISPID_COMMANDSTATECHANGE, OnCommandStateChange, &CommandStateChangeInfo)
		SINK_ENTRY_INFO(37, DIID_DWebBrowserEvents2, DISPID_DOWNLOADBEGIN, OnDownloadBegin, &DownloadInfo)
		SINK_ENTRY_INFO(37, DIID_DWebBrowserEvents2, DISPID_DOWNLOADCOMPLETE, OnDownloadComplete, &DownloadInfo)
	END_SINK_MAP()

	virtual void __stdcall OnBeforeNavigate2 (
	IDispatch* pDisp, VARIANT* URL, VARIANT* Flags, VARIANT* TargetFrameName,
	VARIANT* PostData, VARIANT* Headers, VARIANT_BOOL* Cancel ){}
	virtual void __stdcall OnNavigateComplete2 ( IDispatch* pDisp, VARIANT * URL ){}
	virtual void __stdcall OnStatusChange ( BSTR bsText ){}
	virtual void __stdcall OnDownloadBegin(){}
	virtual void __stdcall OnDownloadComplete(){}
	virtual void __stdcall OnCommandStateChange ( long lCmd, VARIANT_BOOL vbEnabled )
	{
		bool bFlag = (vbEnabled != VARIANT_FALSE);

		if ( CSC_NAVIGATEBACK == lCmd )
		{
			bBackEnable = bFlag;
			//OutputDebugString(CString("OnCommandStateChange Back=%d\n" , bBackEnable));

		}
		else if ( CSC_NAVIGATEFORWARD == lCmd )
		{
			bForwardEnable = bFlag;
			//OutputDebugString(CString("OnCommandStateChange Forward=%d\n" , bForwardEnable));
		}
	}

};
