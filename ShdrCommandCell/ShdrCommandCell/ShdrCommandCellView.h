//
// ShdrCommandCellView.h : interface of the CShdrCommandCellView class
//

#pragma once
#include "ListControl/ListCtrl.h"
#include "NIST/ShdrBackEnd.h"

class CAgentCfg;

class CShdrCommandCellView : public CDialogImpl<CShdrCommandCellView>
{
public:
	enum { IDD = IDD_SHDRCOMMANDCELL_FORM };
	CShdrCommandCellView() 
	{
		m_wndListCtrl.RegisterClass();
	}
	CStatic							_devicetype;
	CStatic							_socketnumber;
	CStatic							_devicename;

	CShdrBackEnd					_shdr;
	CAgentCfg *						_cmdAgentCfg;
	CAgentCfg *						_devicesAgentCfg;

	void							SetCmdAgent(CAgentCfg * cmdAgentCfg){ _cmdAgentCfg=cmdAgentCfg; }
	void							SetDevicesAgent(CAgentCfg * devicesAgentCfg) { _devicesAgentCfg=devicesAgentCfg; }
	MTConnectDataModel	&			DataModel() { return _shdr._dataItems; }

	bool GetDataItem(std::string s, CDataItem	& d) { return _shdr.GetDataItem(s, d); }
	int GetRowNumber(std::string item);
	BOOL PreTranslateMessage(MSG* pMsg);

	void Init(std::string devicesxmlfilename, 
		int ipport, 
		std::string devicename);


	BEGIN_MSG_MAP(CShdrCommandCellView)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_HANDLER(IDC_BUTTON2, BN_CLICKED, OnBnClickedButton2)
		NOTIFY_HANDLER_EX(IDC_LISTCTRL, LCN_DBLCLICK, OnDoubleClicked)
		COMMAND_HANDLER(IDC_BUTTON1, BN_CLICKED, OnBnClickedButton1)	
	END_MSG_MAP()
	void InitBasicList();
	void FillRow(int nNewItem, MTConnectDataModel::iterator it );
	void AddLastRow();
	int Tablesize() { return m_wndListCtrl.GetItemCount(); }
	void Update();

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	CListCtrl m_wndListCtrl;
	CImageList m_ilItemImages;
	CFont m_fntCustomFont1;
	CFont m_fntCustomFont2;
	CImageList m_ilListItems;

	LRESULT OnBnClickedButton2(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnDoubleClicked( LPNMHDR lpNMHDR );
	LRESULT OnBnClickedButton1(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
};
