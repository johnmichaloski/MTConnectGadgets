// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Misc.h"
#include "Test840D.h"

class CMainDlg : public CDialogImpl<CMainDlg>, public CUpdateUI<CMainDlg>,
		public CMessageFilter, public CIdleHandler
{
public:
	enum { IDD = IDD_MAINDLG };
	_bstr_t inifile;
	CEdit _cStatus;
	CComboBox _authSecurityCombo;
	CComboBox _impersonationSecurityCombo;

	CComboBox _authnCombo;
	CComboBox _authzCombo;
	CComboBox _authnlevelCombo;
	CComboBox _impersonationlevelCombo;
	CComboBox _usersCombo;
	CDCOMEnums _enums;
	CIPAddressCtrl _ipaddrControl;

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnIdle();

	BEGIN_UPDATE_UI_MAP(CMainDlg)
	END_UPDATE_UI_MAP()

	int n_authLevelComSecurityEnum;
	int n_impLevelComSecurityEnum;

	int n_authnEnum;
	int n_authzEnum;
	int n_authnlevelEnum;
	int n_impersonationlevelEnum;
	CStringVector _users;
	int _nUser;
	_bstr_t sClsid;
	_bstr_t server;
	CString sUserSettings;
	std::map<std::wstring, std::wstring> ParseIni(std::wstring inisection);
		CString status;

	CComPtr<IOPCServer>		_pIOPCServer;
	CComPtr<IOPCItemMgt>	_pIOPCItemMgt;

	BEGIN_MSG_MAP(CMainDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
		COMMAND_HANDLER(ID_CONNECT, BN_CLICKED, OnBnClickedConnect)
		COMMAND_RANGE_CODE_HANDLER(IDC_AUTHNCOMBO, IDC_USERSCOMBO3, CBN_SELCHANGE, OnCbnSelchangeAuthnCombo);
		//COMMAND_HANDLER(IDC_AUTHNCOMBO, CBN_SELCHANGE, OnCbnSelchangeAuthnCombo)
		//COMMAND_HANDLER(IDC_AUTHNCOMBO2, CBN_SELCHANGE, OnCbnSelchangeAuthnCombo)
		//COMMAND_HANDLER(IDC_AUTHZCOMBO3, CBN_SELCHANGE, OnCbnSelchangeAuthnCombo)
		//COMMAND_HANDLER(IDC_AUTHENLEVELCOMBO4, CBN_SELCHANGE, OnCbnSelchangeAuthnCombo)
		//COMMAND_HANDLER(IDC_IMPERSLEVELCOMBO5, CBN_SELCHANGE, OnCbnSelchangeAuthnCombo)
		COMMAND_ID_HANDLER(IDOK, OnCbnEditAuthnCombo)
		//COMMAND_HANDLER(IDC_USERSCOMBO3,CBN_EDITUPDATE, OnCbnEditAuthnCombo)
		//COMMAND_HANDLER(IDC_USERSCOMBO3,CBN_SELENDOK, OnCbnEditAuthnCombo)

		COMMAND_HANDLER(ID_PINGBUTTON, BN_CLICKED, OnBnClickedPingbutton)
		COMMAND_HANDLER(ID_REGISTRYBUTTON, BN_CLICKED, OnBnClickedRegistrybutton)
		
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		// unregister message filtering and idle updates
		CMessageLoop* pLoop = _Module.GetMessageLoop();
		ATLASSERT(pLoop != NULL);
		pLoop->RemoveMessageFilter(this);
		pLoop->RemoveIdleHandler(this);

		return 0;
	}	
	LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		// TODO: Add validation code 
		CloseDialog(wID);
		return 0;
	}

	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		CloseDialog(wID);
		return 0;
	}

	void CMainDlg::CloseDialog(int nVal)
	{
		DestroyWindow();
		::PostQuitMessage(nVal);
	}

	HRESULT Connect(void);
	LRESULT OnBnClickedConnect(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnCbnSelchangeAuthnCombo(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnCbnEditAuthnCombo(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	
	void Save(void);
	void Load(void);
	LRESULT OnBnClickedPingbutton(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedRegistrybutton(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	HRESULT TestOPCGroup(void);
	HRESULT AddOPCItem(std::wstring name) ;

};
