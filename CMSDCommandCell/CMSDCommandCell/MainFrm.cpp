// MainFrm.cpp : implmentation of the CMainFrame class
//

#include "stdafx.h"
#include "resource.h"

#include "CMSDCommandCellView.h"
#include "MainFrm.h"
#include "StdStringFcn.h"
#include "CmdCell.h"
#include "HtmlTable.h"

CMainFrame::CMainFrame()
{
	_cmdAgentCfg.SetHttpPort(81);
	_devicesAgentCfg.SetHttpPort(82);
	_cmdAgentCfg.SetXmlFile("Devices1.xml");
	_cmdAgentCfg.SetCfgFile("Agent1.cfg");
	_cmsd = new CCMSDIntegrator ;
}

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

	m_hWndClient = m_view.Create(m_hWnd, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, WS_EX_CLIENTEDGE);

	UIAddToolBar(m_hWndToolBar);
	UISetCheck(ID_VIEW_TOOLBAR, 1);
	UISetCheck(ID_VIEW_STATUS_BAR, 1);

	// register object for message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->AddMessageFilter(this);
	pLoop->AddIdleHandler(this);

	CMenuHandle menuMain = GetMenu();
	m_view.SetWindowMenu(menuMain.GetSubMenu(WINDOW_MENU_POSITION));

	return 0;
}

LRESULT CMainFrame::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
	agent.stop();

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
LRESULT CMainFrame::OnFileOpen(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	static int n=0;

	static TCHAR strFilter[] = _T("CMSD Files (*.xml)\0*.xml\0");
	CFileDialog fileDlg(TRUE,
		_T("*"),
		NULL,
		OFN_HIDEREADONLY,
		strFilter);			
	if( fileDlg.DoModal ()!=IDOK )
		return 0;


#if 0
	CCMSDCommandCellView* pView = new CCMSDCommandCellView;
	pView->Create(m_view);
	std::string devicename =  StdStringFormat("M%d",n+1);
	std::string xmldevice= fileDlg.m_szFileTitle;
	std::string portnum =  StdStringFormat("%d",7878+n);
	xmldevice=xmldevice.substr( 0, xmldevice.find_last_of( '.' ));
	_cmdAgentCfg.AddDevice(devicename,xmldevice,"127.0.0.1", portnum);
;

	//if(xmldevice=="Command")
	//	_devicesAgentCfg.AddDevice(devicename,"Generic","127.0.0.1", StdStringFormat("%d",7878+n+1));
	//else
	//	_devicesAgentCfg.AddDevice(devicename,"Command","127.0.0.1", StdStringFormat("%d",7878+n+1));

	//_devicesAgentCfg.SetXmlFile(StdStringFormat("Devices%d.xml",n+1));
	//_devicesAgentCfg.SetCfgFile(StdStringFormat("Agent%d.cfg",n+1));
	//_devicesAgentCfg.SetHttpPort(80+n+1);

	pView->SetCmdAgent(&_cmdAgentCfg);
	pView->SetDevicesAgent(&_devicesAgentCfg) ;

	pView->_shdr.Init(fileDlg.m_szFileName, 7878+n, devicename);
//	pView->_shdr.Init(ExeDirectory() + "command.xml", 7878+n, devicename);
	pView->_devicetype.SetWindowText(("Type = " + xmldevice).c_str());
	pView->_socketnumber.SetWindowText(StdStringFormat("Port = %d",7878+n).c_str());
	pView->_shdr.StartHeartbeat();

	m_view.AddPage(pView->m_hWnd,devicename.c_str());
	pView->InitBasicList();
	//_agents.push_back(new CAgentThread(pView));
	//_agents.back()->Start();
	n++;
#endif
	//std::vector<char *> args;
	//args.push_back(fileDlg.m_szFileName);
	//args.push_back(0);
	//agent.thread(1, (const char **) &args[0]);
	m_FileTitle=fileDlg.m_szFileTitle;

	CWtlHtmlView * pView = new CWtlHtmlView();
	pView->Create(m_view,rcDefault,
		"about:blank", 
		WS_CHILD | WS_VISIBLE | WS_VSCROLL,
		WS_EX_CLIENTEDGE);
	m_view.AddPage(pView->m_hWnd,fileDlg.m_szFileTitle);
	_pages.push_back(pView);
	pView->Write("<BR> Hello World");

	agent.cmsd.ParseCMSD(fileDlg.m_szFileName);

	GLogger.AddListener( boost::bind(&CMainFrame::LogMsg, this, _1));
	return 0;
}
LRESULT CMainFrame::OnStart(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
//	if(m_szFileTitle.Empty())
//		return 0;
	std::vector<char *> args;
	args.push_back((char *) m_FileTitle.c_str());
	args.push_back(0);
	agent.thread(1, (const char **) &args[0]);

	return 0;
}
LRESULT CMainFrame::OnDisplayAgent(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
//	header = "Machine,State,InQ,OutQ," + _resourceHandlers[0]->GenerateCSVHeader() + ",Utility<BR>Costs</BR>,Description";
	htmlTable.ClearValues();
	for(int i=0;i<_resourceHandlers.size() ; i++)
	{
		std::string html1=_resourceHandlers[i]->Name() + ",";
		html1+=StateStr(_resourceHandlers[i]->GetState())  + "," ;
		html1+=_resourceHandlers[i]->inqueue.size()  + "," ;
		html1+=_resourceHandlers[i]->outqueue.size()  + "," ;
		if(_resourceHandlers[i]->currentJob!=NULL) html1+="*,"; else html1+="_,";  
		
		html1+= _resourceHandlers[i]->GenerateCSVTiming()  ;
		htmlTable.AddRow(header, html1);
	}


	std::string table = htmlTable.CreateHtmlTable();
	pHtmlView->SetElementId( "Device", table);
	//::Sleep(10);
	return 0;

}

LRESULT CMainFrame::OnFileRun(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	agent.cmsd.ParseCMSD("C:\\Program Files\\NIST\\proj\\MTConnect\\Nist\\MTConnectGadgets\\TESTBED DEMO\\AgentCmd\\GMCasting\\GMCastinglFactoryTestbed.xml");
	_cmsd->MergeCMSD("C:\\Program Files\\NIST\\proj\\MTConnect\\Nist\\MTConnectGadgets\\TESTBED DEMO\\AgentCmd\\GMCasting\\GMCastinglPerfKPI.xml");
	_cmsd->MergeCMSD("C:\\Program Files\\NIST\\proj\\MTConnect\\Nist\\MTConnectGadgets\\TESTBED DEMO\\AgentCmd\\GMCasting\\GMCastingJob.xml");

	_cmsd->MergeCMSD("C:\\Program Files\\NIST\\proj\\MTConnect\\Nist\\MTConnectGadgets\\TESTBED DEMO\\AgentCmd\\GMCasting\\GMCastinglUtilities.xml");
	
	pHtmlView = new CWtlHtmlView();

	pHtmlView->Create(m_view,rcDefault,
		"about:blank", 
		WS_CHILD | WS_VISIBLE | WS_VSCROLL,
		WS_EX_CLIENTEDGE);

	pHtmlView->SetDocumentText(CHtmlTable::CreateHtmlDocument().c_str());
	pHtmlView->SetElementId( "Header", "Casting 1 operation");
	
	m_view.AddPage(pHtmlView->m_hWnd,"Merged CMSD");
	_pages.push_back(pHtmlView);


//	GLogger.AddListener( boost::bind(&CMainFrame::LogMsg, this, _1));


	for(int i=0 ; i< _cmsd->resources->size(); i++)
	{
		Resource * r = (Resource *) _cmsd->resources->at(i).get();
		std::string name = (LPCSTR) r->name;
		if(name.empty() || name == "None")  // something wrong
			continue; 

		CResourceHandler *  _resourceHandler = new CResourceHandler(r, _cmsd);
		_resourceHandler->_identifier = (LPCSTR) r->identifier;
		_resourceHandler->name = name;
		_resourceHandler->SetStateMachineName(name);
		//_resourceHandler->parent=&_resourceHandlers;
		//_resourceHandler->UpdateRate() =
		_resourceHandlers.push_back(_resourceHandler);

		_resourceHandler-> Cycle();
		_resourceHandler-> Cycle();// takes a second clear to read "run"
	/*	std::string dump= _resourceHandler-> ToString();
		dump+= _resourceHandler-> GenerateReport();
		OutputDebugString(dump.c_str());*/
	}

	header = "Machine,State,InQ,OutQ,Current," + _resourceHandlers[0]->GenerateCSVHeader();
	htmlTable.SetHeaderColumns( header);

	CJobCommands * jobs = new CJobCommands(&agent, _cmsd);
	jobs->InitJobs((Job *)  _cmsd->jobs->at(0).get());// there may be multiple jobs - but only 1st counts in our world

	std::string nMaxQueueSize = _cmsd->jobs->at(0)->GetPropertyValue("MaxQueueSize");
	CJobCommands::MaxQueueSize=ConvertString<int>(nMaxQueueSize,2);
 	jobs->Run(jobs,&_resourceHandlers);

	return 0;
}
void CMainFrame::DumpJobs(CJobCommands * jobs)
{
	std::string tmp;
	for(int i=0; i < jobs->size() ; i++)
	{
		tmp+=StdStringFormat("Job %s Part %s\n", jobs->at(i)->_jobId.c_str(), jobs->at(i)->_partid.c_str());
		int _current = jobs->at(i)->_currentstep;
		int j = FindResourceHandler(jobs->at(i)->_ResourceRequired[_current]);
		if(j<0) 
			continue;
		CResourceHandler * resource= _resourceHandlers[j];
		tmp+= resource->ToString();
	}
	OutputDebugString(tmp.c_str());
}


LRESULT CMainFrame::UpdateResourceHandlers()
{	
	for(int i=0 ; i<_resourceHandlers.size(); i++)
	{
		CResourceHandler *  _resourceHandler = _resourceHandlers[i];
		_resourceHandler-> Cycle();
	}
	return 0;
}

//LRESULT CMainFrame::DumpResourceHandlers()
//{	
//	for(int i=0 ; i<_resourceHandlers.size(); i++)
//	{
//		std::string dump= _resourceHandlers[i]-> ToString();
//		dump+= _resourceHandler-> GenerateReport();
//		OutputDebugString(dump.c_str());
//	}
//	return 0;
//}

int CMainFrame::FindResourceHandler(std::string id)
{	
	for(int i=0 ; i<_resourceHandlers.size(); i++)
	{
		CResourceHandler *  _resourceHandler = _resourceHandlers[i];
		if(_resourceHandler->_identifier==id)
			return i;
	}
	return -1;
}
LRESULT CMainFrame::OnFileMerge(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	static int n=0;

	static TCHAR strFilter[] = _T("CMSD Files (*.xml)\0*.xml\0");
	CFileDialog fileDlg(TRUE,
		_T("*"),
		NULL,
		OFN_HIDEREADONLY,
		strFilter);			
	if( fileDlg.DoModal ()!=IDOK )
		return 0;

	//CWtlHtmlView * pView = new CWtlHtmlView();
	//pView->Create(m_view,rcDefault,
	//	"about:blank", 
	//	WS_CHILD | WS_VISIBLE | WS_VSCROLL,
	//	WS_EX_CLIENTEDGE);
	//m_view.AddPage(pView->m_hWnd,fileDlg.m_szFileTitle);
	//_pages.push_back(pView);
	//GLogger.AddListener( boost::bind(&CMainFrame::LogMsg, this, _1));

	_cmsd->MergeCMSD(fileDlg.m_szFileName);

	return 0;
}

LRESULT CMainFrame::OnLogMessage(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	char * str = (char *) wParam;
	_pages.back()->Write(str);
	delete str;
	return 0;
}

void CMainFrame::LogMsg(const TCHAR * msg)
{
	std::string txt(msg);
	ReplaceAll(txt, "\n", "<BR>\n");
	char * str = new char[txt.size()+1];
	strncpy(str,txt.c_str(),txt.size()+1);
	PostMessage(LOG_MSG, (WPARAM) str, 0);

}

LRESULT CMainFrame::OnStopCellAgent(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	agent.stop();
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


LRESULT CMainFrame::OnWindowClose(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	int nActivePage = m_view.GetActivePage();
	if(nActivePage != -1)
		m_view.RemovePage(nActivePage);
	else
		::MessageBeep((UINT)-1);

	return 0;
}

LRESULT CMainFrame::OnWindowCloseAll(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	m_view.RemoveAllPages();
	return 0;
}

LRESULT CMainFrame::OnWindowActivate(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	int nPage = wID - ID_WINDOW_TABFIRST;
	m_view.SetActivePage(nPage);
	return 0;
}
LRESULT CMainFrame::OnStartCellAgent(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	_cmdAgentCfg.Start();
	//::Sleep(2000);
	//_devicesAgentCfg.Start();
	return 0;

}
