// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

#include "MainDlg.h"
#include "StdStringFcn.h"
#include "MtConnectDboard.h"

DWORD	dwWebBrowserCookie; //Save this to get the interface later

CMainDlg::CMainDlg(CDlgThread * thread, CMtConnectDboard* echo):_thread(thread),_echo(echo)
{

}

BOOL CMainDlg::PreTranslateMessage(MSG* pMsg)
{
	return CWindow::IsDialogMessage(pMsg);
}

BOOL CMainDlg::OnIdle()
{
	return FALSE;
}

LRESULT CMainDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	DlgResize_Init();
	// center the dialog on the screen
	CenterWindow();

	sAppTooltip="MtConnectDboard";
	nIcon=0;

	// set icons
	HICON hIcon = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME), 
		IMAGE_ICON, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON), LR_DEFAULTCOLOR);
	SetIcon(hIcon, TRUE);
	HICON hIconSmall = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME), 
		IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
	SetIcon(hIconSmall, FALSE);

	// register object for message filtering and idle updates
	//CMessageLoop* pLoop = _Module.GetMessageLoop();
	CMessageLoop* pLoop = _thread->GetMessageLoop();
	
	ATLASSERT(pLoop != NULL);
	pLoop->AddMessageFilter(this);
	pLoop->AddIdleHandler(this);

	UIAddChildWindowContainer(m_hWnd);

	// Remove Max/Min buttons - if using TrayIcon
	DWORD style = ::GetWindowLong(this->m_hWnd, GWL_STYLE);
	style &= ~(WS_MAXIMIZEBOX); // WS_MINIMIZEBOX NOT WS_THICKFRAME
	::SetWindowLong(this->m_hWnd, GWL_STYLE, style);

	// Install tray icon
	hSmileyIcon = LoadIcon(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME));
	hIdleIcon = LoadIcon(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDI_IDLEICON));
	hStopIcon = LoadIcon(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDI_STOPICON));
	hClearIcon = LoadIcon(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDI_CLEARICON));
	InstallIcon(sAppTooltip, hSmileyIcon, IDR_MENU1);

	CAxWindow wndIE = GetDlgItem(IDC_EXPLORER1);
	HRESULT hr;
	hr = wndIE.QueryControl ( &m_spWebBrowser );

	if ( m_spWebBrowser )
	{
		CComVariant v;  // empty variant
		m_spWebBrowser->Navigate ( CComBSTR("about:blank"), 
			&v, &v, &v, &v );
	}
	//Handle NavigateComplete2 event from the browser, get the document  element, call DispEventAdvise(pDocument). onclick event bubbles, so you  can handle it on the document and get clicks from all contained  elements.
	//DispEventAdvise(m_spWebBrowser); 

	//Then you need to register your interface to be used proccess wide:
	hr = pGIT->RegisterInterfaceInGlobal( (IUnknown*)(IWebBrowser2*)m_spWebBrowser, IID_IWebBrowser2, &dwWebBrowserCookie);

	//std::string html = MTConnectStreamsParser().CreateHtmlDocument();
	//CHtmlTableSnapshots().SetDocumentText(m_spWebBrowser,html);


	// Icon mapping
	std::vector<HICON> icons(2);
	icons[0]=hSmileyIcon; icons[1]=hClearIcon;	StateIconMap["EXECUTING"] = icons; // flashing green
	icons[0]=hSmileyIcon; icons[1]=hSmileyIcon;	StateIconMap["IDLE"] = icons; // idle auto
	icons[0]=hStopIcon;    icons[1]=hStopIcon;	StateIconMap["STOPPED"] = icons; // stopped
	icons[0]=hStopIcon;    icons[1]=hClearIcon;	StateIconMap["FAULT"] = icons; // stopped fault

	this->SetTimer(1, 250); 

	dlgMainThead = ::GetCurrentThread();
	return TRUE;
}

LRESULT CMainDlg::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	AtlTrace("CMainDlg::OnDestroy");
	// unregister message filtering and idle updates
	//CMessageLoop* pLoop = _Module.GetMessageLoop();
	CMessageLoop* pLoop = _thread->GetMessageLoop();
	//if(pLoop == NULL)
	//	return 0;
	pLoop->RemoveMessageFilter(this);
	pLoop->RemoveIdleHandler(this);
	return 0;
}

void CMainDlg::CloseDialog(int nVal)
{
	AtlTrace("CMainDlg::CloseDialog");
	RemoveIcon();
	KillTimer(1);
	HRESULT hr = pGIT->RevokeInterfaceFromGlobal( dwWebBrowserCookie );
	DestroyWindow();
	::PostQuitMessage(0);
	_echo->threadstop();
#if 0
	service->threadstop();			// this calls close
	RemoveIcon();
	KillTimer(1);
	ShowWindow(SW_HIDE);	// pretend going away
	HRESULT hr = pGIT->RevokeInterfaceFromGlobal( dwWebBrowserCookie );
	DestroyWindow();
	::PostQuitMessage(0);
#endif
}
//static void DoEvents( HWND hWnd_i )
//{
//   MSG stMsg = { 0 };
//   while( PeekMessage( &stMsg, hWnd_i, 0, 0, PM_REMOVE ))
//   {
//       TranslateMessage( &stMsg );
//       DispatchMessage( &stMsg );
//    }
//}
void CMainDlg::Close(int nVal)
{	
	AtlTrace("CMainDlg::Close");
	ShowWindow(SW_HIDE);	// pretend going away
	RemoveIcon();
	KillTimer(1);
	//Don't forget to revoke after you are done:
	HRESULT hr = pGIT->RevokeInterfaceFromGlobal( dwWebBrowserCookie );
	PostThreadMessage((DWORD)dlgMainThead,WM_QUIT,0,0); //???
	AtlTrace("CMainDlg::Close PostQuitMessage");
	::Sleep(100);
	MSG msg = { 0 };
		while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
		AtlTrace("CEchoService::stop()) PeekMessage");
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			::Sleep(100);
		}

}

LRESULT CMainDlg::OnSysCommand(UINT message, WPARAM wparam, LPARAM /*lParam*/, BOOL& bHandled)
{
	// There is a system command
	// wparam has the exact command type that it is
	switch( wparam )
	{
	case SC_CLOSE:
		this->CloseDialog(0);
		bHandled=true;
		bHandled=true;
		return 0;
	case SC_MINIMIZE:
		this->ShowWindow(SW_HIDE);
		bHandled=true;
		return 0;

	case SC_MOVE:
		bHandled=false;
		OutputDebugString("You're moving the window!\n");
		// don't interfere with this one, otherwise your window
		// won't move normally when the user tries to move it!
		break;

		/**
		If password protection is enabled by policy, the screen saver is started regardless 
		of what an application does with the SC_SCREENSAVE notification—even if fails to 
		pass it to DefWindowProc.
		*/
	case SC_SCREENSAVE:     // screensaver wants to begin

		return 1;           // returning 0 PREVENTS those things from happening
		// Note about SC_SCREENSAVE:
		// Try this.  Go into your settings and change
		// your screensaver to start after 1 minute.
		// Then run this program and sit and wait
		// for the 1 minute.

		// The funny thing about this, is Windows will
		// keep trying to enter screen saver mode,
		// by sending your app a "message" every
		// half a second or so.

		// If all you do is return 0; from this
		// part, your app will keep on stopping
		// the screensaver from starting.  And
		// Windows will keep asking if it can
		// start the screen saver or not, until
		// the user does something to reset the
		// screensaver-turn-on timer like move the mouse
		// or press a key on the keyboard.

		// if you wait even longer, the same thing
		// happens with SC_MONITORPOWER, except
		// you keep getting 2 messages now.

	case SC_MONITORPOWER:   // monitor wants to shut off - powersaver mode
		return 1;           // returning 0 PREVENTS monitor from turning off
		//case SC_CLOSE:  //??
	case SC_MAXIMIZE:
		bHandled=false;
		return 0;
		break;

	default:
		bHandled=false;
	} // end wparam inner switch
	return 0;
} // end WndProc


LRESULT  CMainDlg::OnTrayIcon(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	switch(lParam)
	{
	case WM_LBUTTONDBLCLK:
		this->ShowWindow(SW_SHOW);
		break;
	case WM_RBUTTONDOWN:
	case WM_CONTEXTMENU:
		{
			CTrayIconImpl<CMainDlg> ::OnTrayIcon(uMsg, wParam, lParam, bHandled);
		}
		break;
	}
	return 0;
}
LRESULT CMainDlg::OnTimer(UINT message, WPARAM wparam, LPARAM /*lParam*/, BOOL& bHandled)\
{
	HICON icon;

	nIcon=++nIcon%2;
	if(StateIconMap.find(state)!=StateIconMap.end())
	{
		std::vector<HICON> icons = StateIconMap[state];
		if(icons[0]!=icons[1])
		{
			ChangeIcon(icons[nIcon]);
		}
	}
	return 0;
}
