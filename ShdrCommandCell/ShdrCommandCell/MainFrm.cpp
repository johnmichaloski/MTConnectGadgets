// MainFrm.cpp : implmentation of the CMainFrame class
//

#include "stdafx.h"
#include "resource.h"

#include "ShdrCommandCellView.h"
#include "MainFrm.h"
#include "StdStringFcn.h"
#include "ShdrDlg.h"
#include "Yaml.h"
#include "WtlHtmlView.h"

CMainFrame::CMainFrame()
{
	_cmdAgentCfg.SetHttpPort(81);
	_cmdAgentCfg.SetXmlFile("Devices1.xml");
	_cmdAgentCfg.SetCfgFile("Agent1.cfg");
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
	static int n=0;

	CShdrDlg dlg;
	if(dlg.DoModal()!=IDOK )
		return 0;
	for(int i=0; i< dlg.devices.size(); i++)  // array of types of devices
	{
		CShdrCommandCellView* pView = new CShdrCommandCellView;
		pView->Create(m_view);
		int nPort = ConvertString<int>(dlg.ports[i], 7878);
		pView->Init(dlg.devicefiles[i], nPort, dlg.names[i]);
	 	pView->_shdr.StartHeartbeat();

		std::string xmldevice = ExtractFilename(dlg.devicefiles[i]);;
		xmldevice=xmldevice.substr( 0, xmldevice.find_last_of( '.' )) ;

		_cmdAgentCfg.AddDevice(dlg.names[i],xmldevice,"127.0.0.1", dlg.ports[i]);

		m_view.AddPage(pView->m_hWnd,dlg.names[i].c_str());// device name
		pView->InitBasicList();
	}
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

class CHttpPortDlg : public CDialogImpl<CHttpPortDlg>
{
public:
	enum { IDD = IDD_HTTPPORT_DLG	 };
	CString _httpport;

	BEGIN_MSG_MAP(CHttpPortDlg)
		COMMAND_ID_HANDLER(IDOK, OnOK)
		REFLECT_NOTIFICATIONS()
	END_MSG_MAP()
	LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		CWindow(this->GetDlgItem(IDC_PORTEDIT)).GetWindowText( _httpport); // rough guess to port numbering
		EndDialog(wID);
		return 0;
	}

};
LRESULT CMainFrame::OnStartCellAgent(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{

	if(_cmdAgentCfg.devices.size() < 1)
	{
		MessageBox("No devices for agent to communicate with", "Error", MB_OK);
		return 0;
	}
	CHttpPortDlg dlg;
	dlg.DoModal();

	CWtlHtmlView*	pAgentView = new CWtlHtmlView;
	int nHttpPort = ConvertString<int>((LPCSTR) dlg._httpport, 81);
	
	std::string url = ::ExeDirectory() + "jsmtconnect.html";
	std::string contents;
	LoadHtmlResource(contents, IDR_HTML1, ::GetModuleHandle(NULL));
	contents=ReplaceOnce(contents,"127.0.0.1", StdStringFormat("127.0.0.1:%d", nHttpPort));
	WriteFile(url, contents);
	pAgentView->Create(m_view, rcDefault, url.c_str() , WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_HSCROLL | WS_VSCROLL, 0);
	m_view.AddPage(pAgentView->m_hWnd, _T("Agent Status"));

	_cmdAgentCfg.SetHttpPort(nHttpPort) ;
	_cmdAgentCfg.Start();
	return 0;

}


LRESULT CMainFrame::OnOpenCfg(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& bHandled)
{
static TCHAR strFilter[] = _T("CFG Files (*.cfg)\0*.cfg\0");

	CFileDialog dlg(TRUE,
		_T("*.cfg"),
		(::ExeDirectory() + "Agent.cfg").c_str(),
		OFN_HIDEREADONLY,
		strFilter);
	if( dlg.DoModal() != IDOK )
		return 0;

	//_cmdAgentCfg.SetDestinationFolder(::ExtractDirectory( dlg.m_szFileName));

	//size_t endpos = _cfgfolder.find_last_of("\\"); 
	//if(std::string::npos != endpos ) 
	//	_cfgfolder = _cfgfolder.substr( 0, endpos+1 ); 		 

	//std::vector<std::string> devices = ParseDevices((_cfgfolder+"devices.xml").c_str());

	_cmdAgentCfg.Clear();

	Yaml storage;
	//try {
		ParseIniFile(dlg.m_szFileName, storage );
		Yaml yaml = storage.GetSection("Adapters");
		std::vector<std::string> adapters = yaml.GetSections();
		for(int i=0; i< adapters.size(); i++)
		{
			Yaml section =  yaml.GetSection(adapters[i]);

			std::string xmldevice = section.keys["DeviceXml"];
			std::string name = adapters[i];
			std::string port = section.keys["Port"];
			std::string xmldevicepath = _cmdAgentCfg.FindXmlDevicesFilePath(xmldevice);
					
			CShdrCommandCellView* pView = new CShdrCommandCellView;
			pView->Create(m_view);
			int nPort = ConvertString<int>(port, 7878);
			pView->Init(xmldevicepath, nPort, name);
			pView->_shdr.StartHeartbeat();

			_cmdAgentCfg.AddDevice(name,xmldevice,"127.0.0.1", port);

			m_view.AddPage(pView->m_hWnd,name.c_str());// device name
			pView->InitBasicList();
		}
	/*}
	catch(...)
	{

	}*/
	return 0;
}

LRESULT CMainFrame::OnSaveCfg(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	_cmdAgentCfg.OnSaveCfg();

	return 0;

}