//
// TableForm.h : interface of the CTableFormView class
//

#pragma once
#include "Resource.h"
#include "ListCtrl.h"
#include "Config.h"
#include "CMSDIntegrator.h"

class CTableFormView : public CAxDialogImpl<CTableFormView>,
	public CDialogResize<CTableFormView>
{
public:
	enum { IDD = IDD_FORMVIEW };

	struct CUndo
	{
		enum UndoOp { UndeleteRow, UninsertRow, UnoverwriteCell, ReoverwriteCell,
		ReinsertRow};
		UndoOp _op;
		CTableFormView * _pTable;
		int _row;
		int _col;
		IObjectPtr  _mycopy;
		std::string _value;
		CUndo(UndoOp op, CTableFormView * pTable, int row,	IObjectPtr  mycopy)
			: _op(op), _pTable(pTable), _row(row), _mycopy(mycopy) {}
		CUndo(UndoOp op, CTableFormView * pTable, int row, int col, std::string value)
			: _op(op), _pTable(pTable), _row(row), _col(col), _value(value) {}
		CUndo(UndoOp op, CTableFormView * pTable, int row)
			: _op(op), _pTable(pTable), _row(row) {}

	};
	struct CUndoHandler
	{
		std::vector<CUndo> undolist;
		std::vector<CUndo> redolist;
		bool CanUndo()					{ return undolist.size() > 0; }
		bool CanRedo()					{ return redolist.size() > 0; }
		void Clear()					{ undolist.clear(); redolist.clear(); }
		void ClearRedo()				{ redolist.clear(); }
		void ClearUndo()				{ undolist.clear();}
		LRESULT PushRedo(CUndo r)		{ redolist.push_back(r); return 0; }
		LRESULT PushUndo(CUndo u)		{ undolist.push_back(u); return 0;}
		LRESULT PopRedo()				{ if(redolist.size()> 0) redolist.pop_back();  return 0;}
		LRESULT PopUndo()				{ if(undolist.size()> 0) undolist.pop_back();  return 0;}
		LRESULT ExecRedo() ;
		LRESULT ExecUndo() ;
	};
	
	CTableFormView(std::vector<IObjectPtr> * _objects, IObject::CreatorFcn  creator);

	static CUndoHandler& UndoRef() { static CUndoHandler _undo; return  _undo; }
	void DeleteListItem(int nSelectedRow, std::vector<CUndo> & list= UndoRef().undolist );
	void InsertListItem(int n, IObject * branch , std::vector<CUndo> & list = UndoRef().undolist );
	void SaveListItem(int nSelectedRow, int col, std::string value, std::vector<CUndo> & list = UndoRef().undolist);
	

	BOOL PreTranslateMessage(MSG* pMsg);

	BEGIN_DLGRESIZE_MAP(CTableFormView)
		DLGRESIZE_CONTROL(IDC_LISTCTRL, DLSZ_SIZE_X | DLSZ_SIZE_Y)
	END_DLGRESIZE_MAP()

	BEGIN_MSG_MAP(CTableFormView)
		COMMAND_ID_HANDLER(ID_EDIT_COPY, OnEditCopy)
		COMMAND_ID_HANDLER( ID_EDIT_CUT, OnEditCut)
		COMMAND_ID_HANDLER(ID_EDIT_PASTE, OnEditPaste)

		COMMAND_ID_HANDLER( ID_EDIT_UNDO, OnUndoRedo)
		COMMAND_ID_HANDLER( ID_EDIT_REDO, OnUndoRedo)
		COMMAND_ID_HANDLER( ID_FILE_PRINT, OnPrint)

		

		NOTIFY_HANDLER_EX(IDC_LISTCTRL, LCN_SELECTED, OnSelected)
		NOTIFY_HANDLER_EX(IDC_LISTCTRL, LCN_MODIFIED, OnModified)
		NOTIFY_HANDLER_EX(IDC_LISTCTRL, LCN_DBLCLICK, OnDoubleClicked)
		NOTIFY_HANDLER_EX(IDC_LISTCTRL, LCN_LEFTCLICK, OnClicked)
		NOTIFY_HANDLER_EX(IDC_LISTCTRL, LCN_ENTERCOMBO, OnEnterCombo)
		REFLECT_NOTIFICATIONS()
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		CHAIN_MSG_MAP(CDialogResize<CTableFormView>)
		//ALT_MSG_MAP( 1 )
		//CHAIN_MSG_MAP_ALT( CEditCommands<CMyEditView>, 1 )
	END_MSG_MAP()

	// Handler prototypes (uncomment arguments if needed):
	//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	int Tablesize() { return m_wndListCtrl.GetItemCount(); }
	int GetSelectedItemNum();
	//void DeleteListItem(int n);
	bool PrintData(CString szPageTitle);

	void FillRow(int nNewItem, IObject * branch);
	void AddLastRow();
	void SaveRow(int nNewItem, IObject * branch);
	void InitListItems();
	void InitListColumns();
	LRESULT OnModified( LPNMHDR lpNMHDR );
	LRESULT OnSelected( LPNMHDR lpNMHDR );
	LRESULT OnDoubleClicked( LPNMHDR lpNMHDR );
	LRESULT OnClicked( LPNMHDR lpNMHDR );

	LRESULT OnEnterCombo( LPNMHDR lpNMHDR );
	
	LRESULT OnPrint(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnUndoRedo(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnContext(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnEditCopy(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnEditCut(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnEditPaste(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	CListCtrl m_wndListCtrl;
	CImageList m_ilItemImages;
	CFont m_fntCustomFont1;
	CFont m_fntCustomFont2;
	CImageList m_ilListItems;
	//int TABLESIZE;
	std::vector<IObjectPtr> * objects;
	IObject::CreatorFcn  creator;
	int copyindex;
	IObject * mycopy;

};
