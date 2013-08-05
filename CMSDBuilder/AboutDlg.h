// aboutdlg.h : interface of the CAboutDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>
#include <vector>
#include "CCtlColor.h" 
#include "StdStringFcn.h"
#include <atlscrl.h>
#include "PictureBox.h"
#include "BevelLine.h"
#include "ModuleImpl.h"
#include "ToolTipDialog.h"

class CPropertiesDlg : public CAxDialogImpl<CPropertiesDlg>
{
public:
	CPropertiesDlg(std::string nvpairstr)
	{
		nvpairs = Tokenize(nvpairstr,";");
	}
	enum { IDD = IDD_LISTSEL };
	CEdit cName, cValue, cUnits, cDescription;
	CListBox listbox;
	std::vector<std::string> nvpairs;
	std::string result;
	//std::map<std::string,std::string> namevalue;

	BEGIN_MSG_MAP(CPropertiesDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
		COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
		COMMAND_ID_HANDLER(IDC_ADD, OnAddDeleteCmd)
		COMMAND_ID_HANDLER(IDC_DELETE, OnAddDeleteCmd)
		COMMAND_ID_HANDLER(IDC_EDITBUTTON, OnAddDeleteCmd)	
	END_MSG_MAP()
	std::string GetNameValues() { return result; }
	LRESULT OnAddDeleteCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		cName=GetDlgItem(IDC_NAMEEDIT);
		cValue=GetDlgItem(IDC_VALUEEDIT);
		cUnits=GetDlgItem(IDC_UNITSEDIT);
		cDescription=GetDlgItem(IDC_DESCREDIT);

		listbox=GetDlgItem(IDC_LIST1);
		for(int i=0; i< nvpairs.size(); i++)
		{
			if(nvpairs[i].size() < 1)
				continue;
			listbox.AddString((nvpairs[i]+";").c_str());
		}
		return 0;
	}
	LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		if(wID==IDOK)
		{
			result.clear();
			nvpairs.clear();
			for(int i=0; i< listbox.GetCount(); i++)
			{
				CString text;
				listbox.GetText(i, text);
				result+=(LPCSTR) text; 
			}
		}
		EndDialog(wID);
		return 0;
	}

};

class CTestFormView : public CDialogImpl<CTestFormView>
	,public CDialogResize<CTestFormView>
	,public CScrollImpl<CTestFormView> 
	, public CCtlColored<CTestFormView> 
	, public CToolTipDialog<CTestFormView>
{
public:
	enum { IDD = IDD_FORMVIEW1 };
	CEdit m_edit;
	//std::vector<CModule *> m_module;
	std::vector<CModuleWindow *> m_module;
	std::vector<CPictureBox *> m_walls;
	std::vector<CBevelSquare  *> m_bevellines;

	std::map<std::string, CModuleWindow *> m_moduleMap;
	//std::vector<CPictureBox *> m_walls;
	CRect _rect;
	std::vector<IObjectPtr>  _objects;
	CRect boundingbox;
	CFont m_fntCustomFont1;
	double magnifier;

	CTestFormView()
	{
		magnifier=1;
	}
	BOOL PreTranslateMessage(MSG* pMsg)
	{
		return CWindow::IsDialogMessage(pMsg);
	}
	virtual BOOL OnIdle()
	{
		return FALSE;
	}
	BEGIN_MSG_MAP(CTestFormView)
		CHAIN_MSG_MAP(CToolTipDialog<CTestFormView>)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER( ID_ZOOM_IN, OnZoom)
		COMMAND_ID_HANDLER( ID_ZOOM_OUT, OnZoom)

		if(uMsg != WM_PAINT && uMsg != WM_PRINTCLIENT)
		{
			CHAIN_MSG_MAP(CScrollImpl<CTestFormView>)
		}
		//CHAIN_MSG_MAP(CDialogResize<CTestFormView>)
		CHAIN_MSG_MAP(CCtlColored<CTestFormView>) 
			ALT_MSG_MAP(1)
			CHAIN_MSG_MAP(CScrollImpl<CTestFormView>)
	END_MSG_MAP()
	BEGIN_DLGRESIZE_MAP(CTestFormView)

	END_DLGRESIZE_MAP()
	LRESULT OnZoom(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
		LRESULT CTestFormView::ResetMTConnect(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

		LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
		{
			//DlgResize_Init(false);

			// register object for message filtering and idle updates
			//CMessageLoop* pLoop = _Module.GetMessageLoop();
			//ATLASSERT(pLoop != NULL);
			//pLoop->AddMessageFilter(this);
			//pLoop->AddIdleHandler(this);

			LOGFONT logFont = { 0 };
			logFont.lfCharSet = DEFAULT_CHARSET;
			logFont.lfHeight = 90;
			lstrcpy( logFont.lfFaceName, _T( "Arial" ) );
			//logFont.lfWeight = FW_BOLD;
			logFont.lfItalic = (BYTE)TRUE;
			m_fntCustomFont1.CreatePointFontIndirect( &logFont );
			this->SetFont(m_fntCustomFont1); 

			SetScrollSize(2000, 2000);
			boundingbox.top=0;
			boundingbox.left=0;
			boundingbox.right = 750;
			boundingbox.bottom = 750;
			SetTextBackGround(0xFFFFFF);  
			SetTextColor(RGB(0X60, 0, 0)); 

			//		TTInit();
			TTActivate(TRUE);

			DrawObjects();
			return 0;
		}
		void DrawObjects();


};
class CAboutDlg : public CDialogImpl<CAboutDlg>
{
public:
	enum { IDD = IDD_ABOUTBOX };

	BEGIN_MSG_MAP(CAboutDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
		COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
	END_MSG_MAP()

	// Handler prototypes (uncomment arguments if needed):
	//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
};


class CSelectionDlg : public CDialogImpl<CSelectionDlg>
{
public:
	enum { IDD = IDD_SELECTIONLIST };

	CSelectionDlg(std::vector<std::string> allitems, std::vector<std::string> selecteditems)
		: _allitems(allitems), _selecteditems(selecteditems)
	{

	}
	std::vector<std::string> GetSelectedItems() { return _selecteditems; }

	std::vector<std::string> _allitems;
	std::vector<std::string> _selecteditems;
	CListBox _cAllitems;
	CListBox _cSelectionsitems;
	BEGIN_MSG_MAP(CSelectionDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
		COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
		COMMAND_ID_HANDLER(IDC_UPBUTTON, OnUpDownCmd)
		COMMAND_ID_HANDLER(IDC_DOWNBUTTON, OnUpDownCmd)
		COMMAND_ID_HANDLER(IDC_ADDBUTTON, OnAddRemoveCmd)
		COMMAND_ID_HANDLER(IDC_REMOVEBUTTON, OnAddRemoveCmd)
		COMMAND_ID_HANDLER(IDC_SELECTALLBUTTON, OnSelectAllCmd)
		COMMAND_ID_HANDLER(IDC_UNSELECTALLBUTTON, OnSelectAllCmd)

	END_MSG_MAP()

	// Handler prototypes (uncomment arguments if needed):
	//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnUpDownCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnAddRemoveCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnSelectAllCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
};