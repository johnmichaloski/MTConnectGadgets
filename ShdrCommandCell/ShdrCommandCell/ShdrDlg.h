//
// ShdrDlg.h : interface of the CMainDlg class
//

#pragma once
#include "ListCtrl.h"

class CShdrDlg : public CAxDialogImpl<CShdrDlg>,
		public CDialogResize<CShdrDlg>

{
public:

	CShdrDlg()
	{
		m_wndListCtrl.RegisterClass();
	//	TABLESIZE=1;
	}

	CListCtrl m_wndListCtrl;
	CImageList m_ilItemImages;
	CFont m_fntCustomFont1;
	CFont m_fntCustomFont2;
	CImageList m_ilListItems;
	//int TABLESIZE;
	static int m_nMachines;


	enum { IDD = IDD_SHDRDLG };

	std::vector<std::string> ips, ports, rates, debugs, devices,names, alldevices, devicefiles;
	CListArray < CString > scanComboList;
	CListArray < CString > errorComboList;
	CListArray < CString > allDevicesComboList;
	std::string devicemenustr;
	static int Port0;


	BEGIN_DLGRESIZE_MAP(CShdrDlg)
		DLGRESIZE_CONTROL(IDC_LISTCTRL2, DLSZ_SIZE_X | DLSZ_SIZE_Y)
		DLGRESIZE_CONTROL(IDOK, DLSZ_MOVE_X | DLSZ_MOVE_Y)
		DLGRESIZE_CONTROL(IDCANCEL, DLSZ_MOVE_X | DLSZ_MOVE_Y)
	END_DLGRESIZE_MAP()

	BEGIN_MSG_MAP(CShdrDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
		COMMAND_ID_HANDLER(IDC_MULTICHECK, OnClick)
		COMMAND_ID_HANDLER(ID_FILE_NEW, OnNewCfg)
	
		NOTIFY_HANDLER_EX(IDC_LISTCTRL2, LCN_LEFTCLICK, OnClicked)
		NOTIFY_HANDLER_EX(IDC_LISTCTRL2, LCN_RIGHTCLICK, OnClicked)
		NOTIFY_HANDLER_EX(IDC_LISTCTRL2, LCN_DBLCLICK, OnDoubleClicked)
		NOTIFY_HANDLER_EX(IDC_LISTCTRL2, LCN_SELECTED, OnClicked)
		
		REFLECT_NOTIFICATIONS()
		CHAIN_MSG_MAP(CDialogResize<CShdrDlg>)
	END_MSG_MAP()

	void InitBasicList();
	void FillRow(int i);
	void FillRow(int nNewItem, 
		std::string machinename, 
		std::string ipaddr,
		std::string devicetype,
		std::string portcol
		);

	void DeleteListItem(int nSelectedRow);
	void InsertListItem(int n);
	void AddLastRow();	
	std::string FindConfigFile(std::string name);
	//std::string ReadConfigFile(std::string name);
	void UpdateLists();
	void  Clear();
	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnClick(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnNewCfg(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	
	void UpdateLists(std::string config);
	int Tablesize() { return m_wndListCtrl.GetItemCount(); }
	LRESULT OnClicked( LPNMHDR lpNMHDR );
	LRESULT OnDoubleClicked( LPNMHDR lpNMHDR );

};
