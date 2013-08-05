//
// MainDlg.h : interface of the CMainDlg class
//


#pragma once
#include "Resource.h"
#include "atlstr.h"
#define _WTL_NO_CSTRING
#define _CSTRING_NS	ATL
#include "trayiconimpl.h"
#include <string>
#include <vector>


class CMtConnectDboard;
class CDlgThread;

extern 	DWORD	dwWebBrowserCookie; //Save this to get the interface later


class CMainDlg : public  CAxDialogImpl<CMainDlg>,
	public CUpdateUI<CMainDlg>,
	public CMessageFilter, 
	public CIdleHandler,
	public CDialogResize<CMainDlg>,
	public CTrayIconImpl<CMainDlg> 
{
public:
	CMainDlg(CDlgThread *, CMtConnectDboard*);
	CDlgThread *_thread;
	CMtConnectDboard * _echo;
	CComPtr<IWebBrowser2>	m_spWebBrowser;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnIdle();
	BEGIN_UPDATE_UI_MAP(CMainDlg)
	END_UPDATE_UI_MAP()

	BEGIN_DLGRESIZE_MAP(CMainDlg)
		 DLGRESIZE_CONTROL(IDC_EXPLORER1, DLSZ_SIZE_X|DLSZ_SIZE_Y)
    END_DLGRESIZE_MAP()

	BEGIN_MSG_MAP(CMainDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_SYSCOMMAND, OnSysCommand)
		MESSAGE_HANDLER(WM_TIMER, OnTimer)
		REFLECT_NOTIFICATIONS()
		CHAIN_MSG_MAP(CTrayIconImpl<CMainDlg>)
		CHAIN_MSG_MAP(CDialogResize<CMainDlg>)
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)
	virtual LRESULT OnTrayIcon(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/);
	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnSysCommand(UINT message, WPARAM wparam, LPARAM /*lParam*/, BOOL& bHandled);
	LRESULT OnTimer(UINT message, WPARAM wparam, LPARAM /*lParam*/, BOOL& bHandled);

	HANDLE								dlgMainThead; //Save this to get the interface later
	void							CloseDialog(int nVal);
	void							Close(int nVal);

	////////////////////////////////////
	enum { IDD = IDD_MAINDLG };
	HICON								hSmileyIcon, hIdleIcon, hStopIcon, hClearIcon;
	int									nIcon;
	std::string							state;
	std::map<std::string,std::vector<HICON> > StateIconMap;
	CString								sAppTooltip;

	//CComPtr<IWebBrowser2>				m_spWebBrowser;

	// IE security settings makes getting call backs very iffy
	//void __stdcall OnBeforeNavigate(IDispatch *pDisp,VARIANT *URL,
	//	VARIANT *Flags,VARIANT *TargetFrameName,VARIANT *PostData,VARIANT *Headers,
	//	VARIANT_BOOL *Cancel);

};
