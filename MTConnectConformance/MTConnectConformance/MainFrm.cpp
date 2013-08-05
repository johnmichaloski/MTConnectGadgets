// MainFrm.cpp : implmentation of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

#include "aboutdlg.h"
#include "MTConnectConformanceView.h"
#include "MainFrm.h"

#pragma comment( lib, "msxml2.lib" )
#import <msxml6.dll>


#include "MTConnectStreamsParser.h"

static TCHAR strFilter[] = _T("XML Files (*.xml)\0*.xml\0");
std::vector<std::string> ParseDevices(_bstr_t xmlfile)
{ 
	std::vector<std::string> devices;
	_bstr_t parseError(L"");
	MSXML2::IXMLDOMDocument2Ptr        m_pXMLDoc;
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
			return devices;
		}
		MSXML2::IXMLDOMNodePtr root = m_pXMLDoc->GetdocumentElement();
		MSXML2::IXMLDOMNodeListPtr nodes = root->selectNodes(_bstr_t("//Device/Description"));
		for(int i=0; i< nodes->length; i++)
		{
			MSXML2::IXMLDOMNodePtr pNode = NULL;					
			nodes->get_item(i, &pNode);
			bstr_t device = pNode->Gettext();
			devices.push_back((LPCSTR) device);
		}

	}
	catch(_com_error &e)
	{
		std::string errmsg=e.ErrorMessage();
		AtlTrace(errmsg.c_str());
	}
	return devices;
}
BOOL CMainFrame::PreTranslateMessage(MSG* pMsg)
{
	if(CFrameWindowImpl<CMainFrame>::PreTranslateMessage(pMsg))
		return TRUE;

	return m_tabview.PreTranslateMessage(pMsg);
}

BOOL CMainFrame::OnIdle()
{
	UIUpdateToolBar();
	return FALSE;
}

LRESULT CMainFrame::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	CreateSimpleToolBar();
	CreateSimpleStatusBar();

	const DWORD dwSplitStyle = WS_CHILD | WS_VISIBLE | 	WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
	const DWORD	dwSplitExStyle = WS_EX_CLIENTEDGE | SPLIT_BOTTOMALIGNED;
	m_hWndClient = m_splitter.Create (m_hWnd, rcDefault, NULL,  dwSplitStyle, dwSplitExStyle );

	//m_pane.Create(m_splitter, _T(""), WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);	
	m_msgView.Create(m_splitter, rcDefault, _T("about:blank"),  WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_HSCROLL | WS_VSCROLL, 0);

	m_tabview.Create(m_splitter, rcDefault, _T("about:blank"), WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN , 0);

	//m_pane.SetClient(m_tabview);
	m_splitter.SetSplitterPanes ( m_tabview,  m_msgView  );
	m_splitter.SetSplitterPosPct(75); 


	UIAddToolBar(m_hWndToolBar);
	UISetCheck(ID_VIEW_TOOLBAR, 1);
	UISetCheck(ID_VIEW_STATUS_BAR, 1);

	// register object for message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->AddMessageFilter(this);
	pLoop->AddIdleHandler(this);

//	CMenuHandle menuMain = GetMenu();
	//m_view.SetWindowMenu(menuMain.GetSubMenu(WINDOW_MENU_POSITION));
//m_splitter.SetWindowMenu(menuMain.GetSubMenu(WINDOW_MENU_POSITION));

	m_msgView.SetDocumentText("<HTML><BODY>Ready</BODY></HTML>");
	return 0;
}

LRESULT CMainFrame::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
	// unregister message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->RemoveMessageFilter(this);
	pLoop->RemoveIdleHandler(this);

	bHandled = FALSE;
	return 1;
}

LRESULT CMainFrame::OnFileExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	PostMessage(WM_CLOSE);
	return 0;
}

LRESULT CMainFrame::OnFileNew(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CMTConnectConformanceView* pView = new CMTConnectConformanceView;
	//TODO: Replace with a URL of your choice
	pView->Create(m_tabview, rcDefault, _T("about:blank"), WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_HSCROLL | WS_VSCROLL, 0);
	m_tabview.AddPage(pView->m_hWnd, _T("Document"));
	return 0;
}

LRESULT CMainFrame::OnViewToolBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	BOOL bVisible = !::IsWindowVisible(m_hWndToolBar);
	::ShowWindow(m_hWndToolBar, bVisible ? SW_SHOWNOACTIVATE : SW_HIDE);
	UISetCheck(ID_VIEW_TOOLBAR, bVisible);
	UpdateLayout();
	return 0;
}

LRESULT CMainFrame::OnViewStatusBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	BOOL bVisible = !::IsWindowVisible(m_hWndStatusBar);
	::ShowWindow(m_hWndStatusBar, bVisible ? SW_SHOWNOACTIVATE : SW_HIDE);
	UISetCheck(ID_VIEW_STATUS_BAR, bVisible);
	UpdateLayout();
	return 0;
}

LRESULT CMainFrame::OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CAboutDlg dlg;
	dlg.DoModal();
	return 0;
}

LRESULT CMainFrame::OnWindowClose(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	int nActivePage = m_tabview.GetActivePage();
	if(nActivePage != -1)
		m_tabview.RemovePage(nActivePage);
	else
		::MessageBeep((UINT)-1);

	return 0;
}

LRESULT CMainFrame::OnWindowCloseAll(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	m_tabview.RemoveAllPages();

	return 0;
}

LRESULT CMainFrame::OnWindowActivate(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	int nPage = wID - ID_WINDOW_TABFIRST;
	m_tabview.SetActivePage(nPage);

	return 0;
}

LRESULT CMainFrame::OnFileOpen(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CFileDialog dlg(TRUE,
		_T("*"),
		NULL,
		OFN_HIDEREADONLY,
		strFilter);
	if( dlg.DoModal() != IDOK )
		return 0;
	//xsdfile = "http://www.mtconnect.org/schemas/MTConnectStreams_1.2.xsd";
	xsdfile = "file:///C:\\Program Files\\NIST\\proj\\MTConnect\\Nist\\MTConnectGadgets\\MTConnectConformance\\MTConnectConformance\\Debug\\MTConnectStreams_1.2.xsd";
	xmlfile=dlg.m_szFileName;

	CMTConnectConformanceView* pView = new CMTConnectConformanceView;
	pView->Create(m_tabview, rcDefault, dlg.m_szFileName, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_HSCROLL | WS_VSCROLL, 0);
	m_tabview.AddPage(pView->m_hWnd, _T("Document"));

	return 0;
}

LRESULT CMainFrame::OnToolsConformance(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	MTConnectStreamsParser parser;
	m_msgView.Clear();
	std::string errormsg = parser.ParseXMLDocument(xmlfile.c_str(), 
		xsdfile.c_str(),
		"urn:mtconnect.org:MTConnectStreams:1.2");

	if(errormsg.size() == 0)
		errormsg="No errors";
	m_msgView.SetDocumentText("<HTML><BODY>" + errormsg +
		"</BODY></HTML>");

	return 0;
}
