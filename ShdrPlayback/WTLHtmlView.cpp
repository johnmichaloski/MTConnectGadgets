// P21toHtmlView.cpp : implementation of the CWtlHtmlView class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

#include "WtlHtmlView.h"
#include "docobj.h"
#include "comutil.h"

CWtlHtmlView::CWtlHtmlView()
{
	m_pBody = NULL;
	m_spHTMLDocument= NULL;
	m_spWebBrowser2= NULL;
	m_spWebBrowser= NULL;
	bBackEnable=true;
	bForwardEnable=true;

}
CWtlHtmlView::~CWtlHtmlView()
{
	if(m_spWebBrowser2!=NULL)
	{
		DispEventUnadvise ( m_spWebBrowser2 );
	}
}
BOOL CWtlHtmlView::PreTranslateMessage(MSG* pMsg)
{
	if((pMsg->message < WM_KEYFIRST || pMsg->message > WM_KEYLAST) &&
	   (pMsg->message < WM_MOUSEFIRST || pMsg->message > WM_MOUSELAST))
		return FALSE;

	// give HTML page a chance to translate this message
	return (BOOL)SendMessage(WM_FORWARDMSG, 0, (LPARAM)pMsg);
}
LRESULT CWtlHtmlView::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	return 0;
}

BOOL CWtlHtmlView::GetBody()
{
	CComPtr<IDispatch> pDisp;
	CComVariant ve;
	// navOpenInNewWindow, navNoHistory,navNoReadFromCache,navNoWriteToCache
	// navAllowAutosearch,navBrowserBar,navHyperlink
	CComVariant vBrowserNav; 
	if(m_spHTMLDocument!=NULL)
		return 0;
	// Get the browser interface from the embedded HTML control
	if((m_spWebBrowser==NULL) && FAILED(QueryControl(__uuidof(IWebBrowser), reinterpret_cast<void**>(&m_spWebBrowser))) )
		m_spWebBrowser=NULL;

	if( SUCCEEDED(QueryControl(__uuidof(m_spWebBrowser2), reinterpret_cast<void**>(&m_spWebBrowser2))) )
	{
		if(m_spWebBrowser2!=NULL)
		{
			DispEventAdvise ( m_spWebBrowser2 );
			if(FAILED(m_spWebBrowser2->get_Document( &pDisp)))
				OutputDebugString("get_Document Failed");
			if(pDisp!=NULL) 
			{
				if(FAILED(pDisp->QueryInterface(IID_IHTMLDocument2, (void**)&m_spHTMLDocument))) 
					OutputDebugString("QI IID_IHTMLDocument2 Failed");
			}

		}

	}
	return FALSE;
}
HRESULT CWtlHtmlView::SetDocumentText( CString cstr)
{
	_bstr_t str(cstr);
	HRESULT hr = S_OK;
	VARIANT *param;
	SAFEARRAY *sfArray;
	IHTMLDocument2 *document;
	BSTR bstr = str.Detach();

	// Creates a new one-dimensional array
	sfArray = SafeArrayCreateVector(VT_VARIANT, 0, 1);

	if(m_spHTMLDocument==NULL)
		this->GetBody();

	document= m_spHTMLDocument;
	if (sfArray == NULL || document == NULL) {
		hr=E_FAIL;
		goto cleanup;
	}

	hr = SafeArrayAccessData(sfArray,(LPVOID*) & param);
	param->vt = VT_BSTR;
	param->bstrVal = bstr;
	hr = SafeArrayUnaccessData(sfArray);
	hr = document->write(sfArray);

cleanup:
	if (sfArray != NULL) {
		SafeArrayDestroy(sfArray);
	}
	return hr;
}
HRESULT CWtlHtmlView::Navigate(CString url)
{
	USES_CONVERSION;
	CComVariant vurl((BSTR) T2W( url));
	CComVariant ve;
	CComVariant vBrowserNav; 
	GetBody();
	return m_spWebBrowser2->Navigate2(&vurl,
					&vBrowserNav, 
					&ve, //TargetFrameName _BLANK  _PARENT  _SELF _TOP  
					&ve, &ve);

}

bool CWtlHtmlView::QueryStatus( OLECMDID nCmdID, int value) 
{
	OLECMDF eQuery ; //      'return value type for QueryStatusWB
	if(m_spWebBrowser2==NULL)
		return false;

	if(FAILED( m_spWebBrowser2->QueryStatusWB(OLECMDID_PRINT, &eQuery))) //  'get print command status
		return false;

	if(( eQuery & value) )
		return true;
	return false;
}



//OLECMDID_PRINT	= 6,
HRESULT CWtlHtmlView::ExecCommand( OLECMDID nCmdID, OLECMDEXECOPT nCmdExecOpt, VARIANTARG* pvarargIn, VARIANTARG* pvarargOut) 
{
	HRESULT hr=S_OK;
	LPDISPATCH lpDispatch = NULL;
	LPOLECOMMANDTARGET lpOleCommandTarget = NULL;
	try {

		m_spWebBrowser->get_Document(&lpDispatch);
		if(lpDispatch==NULL)
			throw;
		OLECMDF eQuery ; //      'return value type for QueryStatusWB

		if(FAILED( m_spWebBrowser2->QueryStatusWB(OLECMDID_PRINT, &eQuery))) //  'get print command status
			throw;

		if(!( eQuery & OLECMDF_ENABLED) )
			throw;

		lpDispatch->QueryInterface(IID_IOleCommandTarget, (void**)&lpOleCommandTarget);
		if(lpOleCommandTarget==NULL)
			throw;

		// Print contents of WebBrowser control.
		hr=lpOleCommandTarget->Exec(NULL, nCmdID, nCmdExecOpt, pvarargIn, pvarargOut);
	}
	catch(...)
	{
		hr=E_FAIL;
	}
	if(lpDispatch)
		lpDispatch->Release();
	if(lpOleCommandTarget)
		lpOleCommandTarget->Release();
	return hr;
}

//OLECMDID_PRINT	= 6,
HRESULT CWtlHtmlView::OnExecCommand( OLECMDID nCmdID, OLECMDEXECOPT nCmdExecOpt, VARIANTARG* pvarargIn, VARIANTARG* pvarargOut) 
{
	return m_spWebBrowser2->ExecWB(nCmdID, nCmdExecOpt, pvarargIn, pvarargOut);
	
}

void CWtlHtmlView::GoBack() 
{
	if(m_spWebBrowser==NULL && FAILED(QueryControl(__uuidof(IWebBrowser), reinterpret_cast<void**>(&m_spWebBrowser))) )
		return;
	m_spWebBrowser->GoBack();


}
void CWtlHtmlView::GoForward() 
{
	if(m_spWebBrowser==NULL && FAILED(QueryControl(__uuidof(IWebBrowser), reinterpret_cast<void**>(&m_spWebBrowser))) )
		return;
	m_spWebBrowser->GoForward();

}
void CWtlHtmlView::Refresh()
{
	if (m_spWebBrowser != NULL) {
		m_spWebBrowser->Refresh();
	}
}
IHTMLDocument2 *CWtlHtmlView::GetDocument()
{
	IHTMLDocument2 *document = NULL;
	
	if (m_spWebBrowser != NULL) {
	
		// get browser document's dispatch interface

		IDispatch *document_dispatch = NULL;

		HRESULT hr = m_spWebBrowser->get_Document(&document_dispatch);

		if (SUCCEEDED(hr) && (document_dispatch != NULL)) {

			// get the actual document interface

			hr = document_dispatch->QueryInterface(IID_IHTMLDocument2,
			                                       (void **)&document);

			// release dispatch interface					
			document_dispatch->Release();	
		}	
	}	
	return document;
}
void CWtlHtmlView::Write(LPCTSTR string)
{
	if (m_spWebBrowser == NULL)
	GetBody();

	if (m_spWebBrowser != NULL) {

		// get document interface

		IHTMLDocument2 *document = GetDocument();
		
		if (document != NULL) {

			// construct text to be written to browser as SAFEARRAY

			SAFEARRAY *safe_array = SafeArrayCreateVector(VT_VARIANT,0,1);
			
			VARIANT	*variant;
			
			SafeArrayAccessData(safe_array,(LPVOID *)&variant);
			
			variant->vt      = VT_BSTR;
			variant->bstrVal = CString(string).AllocSysString();
			
			SafeArrayUnaccessData(safe_array);

			// write SAFEARRAY to browser document

			document->write(safe_array);
			
			document->Release();
			document = NULL;

		}

	}
}

void CWtlHtmlView::Clear()
{
	if (m_spWebBrowser != NULL) {

		// if document interface available, close/re-open document to clear display

		IHTMLDocument2	*document	= GetDocument();
		HRESULT			hr			= S_OK;
		
		if (document != NULL) {

			// close and re-open document to empty contents

			document->close();
			
			VARIANT		open_name;
			VARIANT		open_features;
			VARIANT		open_replace;
			IDispatch	*open_window	= NULL;

			::VariantInit(&open_name);

			open_name.vt      = VT_BSTR;
			open_name.bstrVal = ::SysAllocString(L"_self");

			::VariantInit(&open_features);
			::VariantInit(&open_replace);
			
			hr = document->open(::SysAllocString(L"text/html"),
			                    open_name,
			                    open_features,
			                    open_replace,
			                    &open_window);

			if (hr == S_OK) {
				Refresh();
			}

			if (open_window != NULL) {
				open_window->Release();
			}

		}

		// otherwise, navigate to about:blank and wait for document ready

		else {

			Navigate(_T("about:blank"));

			IHTMLDocument2 *document = NULL;
			HRESULT			hr       = S_OK;

			while ((document == NULL) && (hr == S_OK)) {

				Sleep(0);

				IDispatch *document_dispatch = NULL;

				hr = m_spWebBrowser->get_Document(&document_dispatch);

				// if dispatch interface available, retrieve document interface
				
				if (SUCCEEDED(hr) && (document_dispatch != NULL)) {

					// retrieve document interface
					
					hr = document_dispatch->QueryInterface(IID_IHTMLDocument2,(void **)&document);

					document_dispatch->Release();

				}
				
			}
			
			if (document != NULL) {
				document->Release();	
			}

		}
		
	}
}