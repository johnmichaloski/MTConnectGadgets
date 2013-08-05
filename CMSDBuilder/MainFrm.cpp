// MainFrm.cpp : implmentation of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

#include "aboutdlg.h"
#include "CMSDBuilderView.h"
#include "MainFrm.h"

#ifdef ARENA
#include "ComArenaHook.h"
#endif

static TCHAR strFilter[] = _T("XML Files (*.xml)\0*.xml\0All Files (*.*)\0*.*\0");

CMainFrame::CMainFrame()
{
	for(int i=0; i< IObject::GetAllObjects().size(); i++)
	{
		m_tabviews.push_back(new CTableFormView((std::vector<IObjectPtr> *) IObject::GetAllObjects()[i],
			IObject::GetAllCreators()[i]
		));
		bstr_t classname = IObject::GetAllCreators()[i]()->GetClassname();
		m_tabmapviews[(LPCSTR) classname]= m_tabviews[i];
	}
}
BOOL CMainFrame::PreTranslateMessage(MSG* pMsg)
{
	if(CFrameWindowImpl<CMainFrame>::PreTranslateMessage(pMsg))
		return TRUE;

	return m_treeview.PreTranslateMessage(pMsg);
}
BOOL CMainFrame::OnIdle()
{
	UIUpdateToolBar();
	UIEnable(ID_EDIT_UNDO, CTableFormView::UndoRef().CanUndo());
	UIEnable(ID_EDIT_REDO, CTableFormView::UndoRef().CanRedo());
	 UIEnable(ID_EDIT_PASTE, ::IsClipboardFormatAvailable(CF_TEXT));
	return FALSE;
}
CTableFormView * CMainFrame::GetTableFormView(std::string name)
{
	std::map<std::string, CTableFormView*>::iterator it;
	it=m_tabmapviews.find(name);
	if(it!=m_tabmapviews.end())
		return m_tabmapviews[name];
	return NULL;

}

LRESULT CMainFrame::OnCreateResourcesFromLayout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	std::map<std::string, CModuleWindow *> modules = m_formview.m_moduleMap;
	std::map<std::string, CModuleWindow *>::iterator it;
	
	for(it = modules.begin(); it!=modules.end(); it++)
	{
		Resource * aresource  ((Resource *) IObject::CreateSave<Resource>());
		aresource->name=(*it).first.c_str();
		aresource->identifier=(*it).first.c_str();
	}
	
	CTableFormView *  pView = GetTableFormView("Resource");
	if(pView) pView->InitListItems();
	return 0;
}

intptr_t CMainFrame::Spawn(int modeflag, std::string cmd, std::string argv)
{
	const char *args[2];
	args[0] = argv.c_str();
	args[1] = 0;
	return spawnvp(modeflag, cmd.c_str(), args) ;
}
LRESULT CMainFrame::OnGoMotion(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	std::string gocmd =  IObject::config.GetSymbolValue("GOMOTION.Command").c_str();
	std::string goargv =  IObject::config.GetSymbolValue("GOMOTION.Argv").c_str();
	std::string ip =  IObject::config.GetSymbolValue("GOMOTION.Ip").c_str();
	std::string devicesxml =  IObject::config.GetSymbolValue("GOMOTION.DevicesXML").c_str();
	int port = 7878;

	std::map<std::string, CModuleWindow *> resources = m_formview.m_moduleMap;
	std::map<std::string, CModuleWindow *>::iterator it;


	std::string agentcfg;
	for(it = resources.begin(); it!=resources.end(); it++)
	{
		std::string sport=StdStringFormat("%d",port++);
		std::string argv=" " + goargv;;
		argv=ReplaceOnce(argv, "7878", sport);
#if 1
		intptr_t pid = Spawn(_P_NOWAIT, gocmd, argv) ;
		shdrpids.push_back((HANDLE)pid);
		::Sleep(1000);
		// May not find resource and will throw exception
		Layout* r = xml.FindLayoutByAssociatedResource((*it).first.c_str());
		//Resource * r = xml.FindResourceByName((*it).first.c_str());
		std::string rip = ip + "/" + (*it).first;
		r->AddProperty("MTConnect", rip , "","");
#endif
		agentcfg+=(*it).first  + "," + devicesxml + "," + ip + "," + sport+"\n";
	}
	// Run agent configuration
	std::string agentcfgdest =  IObject::config.GetSymbolValue("AGENTCFG.Destination").c_str();
	std::string agentcfgcmd =  IObject::config.GetSymbolValue("AGENTCFG.Command").c_str();
	std::string restartcmd =  IObject::config.GetSymbolValue("AGENTCFG.Restart").c_str();
	//std::string tmpfilename = WriteTempFile("AgentCfg", agentcfg);
	std::string tmpfilename = "C:\\Temp\\Agent.cfg";
	WriteFile(tmpfilename, agentcfg);

	::Sleep(1000);
	std::string argv=" -f \"" + tmpfilename  + "\"" ; // cfgfilename
	argv+= " -p 80 ";
	argv+= "-d \""+agentcfgdest+"\"";
	intptr_t pid = Spawn(_P_WAIT, agentcfgcmd, argv) ;
	pid = Spawn(_P_NOWAIT, agentcfgdest+"\\Agent.exe", " debug") ;


	BOOL bHandled;
	m_formview.ResetMTConnect(0,0,0, bHandled);

	return 0;
}
LRESULT CMainFrame::OnKillAdapters(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	for(int i=0; i<shdrpids.size(); i++)
		TerminateProcess((HANDLE) shdrpids[i], 0);
	shdrpids.clear();
	return 0;
}

LRESULT CMainFrame::OnFileNew(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	for(int i=0; i< IObject::GetAllObjects().size(); i++)
	{
		IObject::GetAllObjects()[i]->clear();
		
	}
	for(int i=0; i< m_tabviews.size(); i++)
	{
		m_tabviews[i]->InitListItems();
	}
	filename.empty();
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
		
	filename=dlg.m_szFileName;
	xml.Clear();

	//hook.JobShopBuilder((::ExeDirectory() + "JobShop.xml").c_str());
	//hook.xml.ParseCMSD((::ExeDirectory() + "JobShop.xml").c_str());

	// FIXME: add parse test for validity XMLness, then CMSDness
	xml.ParseCMSD(dlg.m_szFileName);
	//hook.xml.SaveCMSD((::ExeDirectory() + "JobShop1.xml").c_str());
	//m_treeview.PopulateTree(&xml);
	for(int i=0; i< m_tabviews.size(); i++)
	{
		m_tabviews[i]->InitListItems();
	}

	m_formview.DrawObjects();

	return 0;
}

LRESULT CMainFrame::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// create command bar window
	HWND hWndCmdBar = m_CmdBar.Create(m_hWnd, rcDefault, NULL, ATL_SIMPLE_CMDBAR_PANE_STYLE);
	// attach menu
	m_CmdBar.AttachMenu(GetMenu());
	// load command bar images
	m_CmdBar.LoadImages(IDR_MAINFRAME);
	// remove old menu
	SetMenu(NULL);

	HWND hWndToolBar = CreateSimpleToolBarCtrl(m_hWnd, IDR_MAINFRAME, FALSE, ATL_SIMPLE_TOOLBAR_PANE_STYLE);

	CreateSimpleReBar(ATL_SIMPLE_REBAR_NOBORDER_STYLE);
	AddSimpleReBarBand(hWndCmdBar);
	AddSimpleReBarBand(hWndToolBar, NULL, TRUE);

	CreateSimpleStatusBar();

	m_hWndClient = m_splitter.Create(m_hWnd, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

	m_pane.SetPaneContainerExtendedStyle(PANECNT_NOBORDER);
	m_pane.Create(m_splitter, _T("Tree"), WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
	m_treeview.Create(m_pane, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_SHOWSELALWAYS, WS_EX_CLIENTEDGE);
	m_treeview.SetFont(AtlGetDefaultGuiFont());
	m_pane.SetClient(m_treeview);

	//TODO: Replace with a URL of your choice
	//m_view.Create(m_splitter, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_SHOWSELALWAYS, WS_EX_CLIENTEDGE);
	//m_view.Create(m_splitter, rcDefault, _T("about:blank"), WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_HSCROLL | WS_VSCROLL, WS_EX_CLIENTEDGE);
	
	//m_view.Create(m_splitter);

	m_view.Create(m_splitter, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, WS_EX_CLIENTEDGE);
	
	m_formview.Create(m_view);
	m_view.AddPage(m_formview.m_hWnd, "Plant Layout");


	for(int i=0; i< m_tabviews.size(); i++)
	{
		m_tabviews[i]->Create(m_view);
		m_view.AddPage(m_tabviews[i]->m_hWnd, IObject::GetAllClassnames()[i].c_str());
	}



	m_splitter.SetSplitterPanes(m_pane, m_view);
	UpdateLayout();
	m_splitter.SetSplitterPosPct(25);

	UIAddToolBar(hWndToolBar);
	UISetCheck(ID_VIEW_TOOLBAR, 1);
	UISetCheck(ID_VIEW_STATUS_BAR, 1);
	UISetCheck(ID_VIEW_TREEPANE, 1);

	// register object for message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->AddMessageFilter(this);
	pLoop->AddIdleHandler(this);

	return 0;
}
LRESULT CMainFrame::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
	MTConnections.Stop();
	MTConnections.Join(2000);

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
LRESULT CMainFrame::OnViewToolBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	static BOOL bVisible = TRUE;	// initially visible
	bVisible = !bVisible;
	CReBarCtrl rebar = m_hWndToolBar;
	int nBandIndex = rebar.IdToIndex(ATL_IDW_BAND_FIRST + 1);	// toolbar is 2nd added band
	rebar.ShowBand(nBandIndex, bVisible);
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
LRESULT CMainFrame::OnViewTreePane(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	bool bShow = (m_splitter.GetSinglePaneMode() != SPLIT_PANE_NONE);
	m_splitter.SetSinglePaneMode(bShow ? SPLIT_PANE_NONE : SPLIT_PANE_RIGHT);
	UISetCheck(ID_VIEW_TREEPANE, bShow);

	return 0;
}
LRESULT CMainFrame::OnTreePaneClose(WORD /*wNotifyCode*/, WORD /*wID*/, HWND hWndCtl, BOOL& /*bHandled*/)
{
	if(hWndCtl == m_pane.m_hWnd)
	{
		m_splitter.SetSinglePaneMode(SPLIT_PANE_RIGHT);
		UISetCheck(ID_VIEW_TREEPANE, 0);
	}

	return 0;
}
LRESULT CMainFrame::OnFileRun(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
//#ifdef ARENA
	CArenaComHook hook;
	hook.JobShopBuilder(xml); // (::ExeDirectory() + "JobShop.xml").c_str());
//#endif
	return 0;
}
LRESULT CMainFrame::OnFileSave(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if(filename.size() < 1)
		return OnFileSaveAs (wNotifyCode, wID, hWndCtl, bHandled);

	xml.SaveCMSD(filename);

	return 0;
}
LRESULT CMainFrame::OnFileSaveAs(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CFileDialog dlg(FALSE,
		_T("*"),
		NULL,
		OFN_OVERWRITEPROMPT|OFN_HIDEREADONLY,
		strFilter);
	if( dlg.DoModal() != IDOK )
		return 0;
	xml.SaveCMSD(dlg.m_szFileName);
	filename=dlg.m_szFileName;

	return 0;
}