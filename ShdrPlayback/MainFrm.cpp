//
// MainFrm.cpp : implmentation of the CMainFrame class
//


// This software was developed by U.S. Government employees as part of
// their official duties and is not subject to copyright. No warranty implied 
// or intended.

#include "stdafx.h"
#include "resource.h"

#include "ShdrFileEchoView.h"
#include "MainFrm.h"

BOOL CMainFrame::PreTranslateMessage(MSG* pMsg)
{
	if(CFrameWindowImpl<CMainFrame>::PreTranslateMessage(pMsg))
		return TRUE;

	return m_view.PreTranslateMessage(pMsg);
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

	m_hWndClient = m_view.Create(m_hWnd);

	UIAddToolBar(m_hWndToolBar);
	UISetCheck(ID_VIEW_TOOLBAR, 1);
	UISetCheck(ID_VIEW_STATUS_BAR, 1);
	UISetCheck(ID_TOOLS_REPEAT, 1);
	UISetCheck(ID_SPEED_100, 1);
	lastSpeedId=ID_SPEED_100;


	
	// register object for message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->AddMessageFilter(this);
	pLoop->AddIdleHandler(this);

	// Init MRU list
	CMenuHandle mainMenu = GetMenu();
	CMenuHandle fileMenu = mainMenu.GetSubMenu(0);
	CMenuHandle mruMenu = fileMenu.GetSubMenu(9);
	m_mru.SetMenuHandle ( mruMenu );
	m_mru.UpdateMenu();
	m_mru.ReadFromRegistry(APP_SETTINGS_KEY);
	m_mru.SetMaxEntries(4);



	UIEnable ( ID_TOOLS_START, true );
    UIEnable ( ID_TOOLS_STOP, false );

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

LRESULT CMainFrame::OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
	this->ShowWindow(SW_HIDE);
	m_view.Close();
	bHandled=false;
	m_mru.WriteToRegistry(APP_SETTINGS_KEY);
	return 0;
}

void CMainFrame::Open(std::string filename)
{
	m_view.Filename() = filename;
	m_view.Open(); // in.open(dlg.m_szFileName); 

}

LRESULT CMainFrame::OnFileOpen(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{

	static TCHAR strFilter[] = { "Any Files (*.*)|*.*||" };

	CFileDialog dlg(TRUE,
		_T("*"),
		NULL,
		OFN_HIDEREADONLY,
		strFilter);
	if( dlg.DoModal() != IDOK )
		return 0;
	SetWindowText(dlg.m_szFileName);
	m_mru.AddToList(dlg.m_szFileName);
	Open(dlg.m_szFileName);
	return 0;
}

LRESULT CMainFrame::OnOpenUsingMRU(WORD nId, WORD wID, HWND, BOOL&) 
{
	TCHAR szDocument[MAX_PATH];
	m_mru.GetFromList(wID, szDocument, MAX_PATH);
	m_mru.MoveToTop(wID);

	Open(szDocument);

	return 0;
}


LRESULT CMainFrame::OnToolsRepeat(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& /*bHandled*/)
{
	bool bRepeat = UIGetState(wID) &  UPDUI_CHECKED;
	UISetCheck(wID, !bRepeat);
	m_view._bRepeat = bRepeat;
	return 0;
}

LRESULT CMainFrame::OnToolsStart(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	UIEnable ( ID_TOOLS_START, false );
    UIEnable ( ID_TOOLS_STOP, true );
	m_view.Start();
	return 0;
}

LRESULT CMainFrame::OnToolsStop(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{

	UIEnable ( ID_TOOLS_START, true );
    UIEnable ( ID_TOOLS_STOP, false );
	return 0;
}

LRESULT CMainFrame::OnSpeed(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{

	if(lastSpeedId==wID)
		return 0;
	UISetCheck(lastSpeedId, 0);
	UISetCheck(wID, 1);
	lastSpeedId=wID;
	double speed=1.0;
	switch(wID)
	{
	case ID_SPEED_50:  speed=2.0; break;
	case ID_SPEED_100: speed=1.0;    break;           
	case ID_SPEED_150:  speed=0.75;    break;                  
	case ID_SPEED_200: speed=.5;    break;                            
	case ID_SPEED_400: speed=.25; break;
	}
	m_view._dOverride = speed;

	return 0;
}

void CMainFrame::Reset()
{
	UIEnable ( ID_TOOLS_START, false );
    UIEnable ( ID_TOOLS_STOP, true );
}

