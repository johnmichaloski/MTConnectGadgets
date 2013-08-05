#include "stdafx.h"
#include "TableForm.h"
#include "AboutDlg.h"
#include "ATLUtils.h"

#define IMGCOLS 1
//CTableFormView::CUndoHandler CTableFormView::_undo;


LRESULT CTableFormView::CUndoHandler::ExecRedo() 
{
	if(UndoRef().redolist.size() < 1)
		return 1;
	CUndo undo = UndoRef().redolist.back();
	if(undo._op == CUndo::UndeleteRow)
	{
		undo._pTable->InsertListItem(undo._row, undo._mycopy.get() , UndoRef().undolist);
	}
	else if(undo._op == CUndo::UninsertRow)
	{
		// Reinsert row that was deleted
		undo._pTable->DeleteListItem(undo._row, UndoRef().undolist); 
	}
	else if(undo._op == CUndo::UnoverwriteCell)
	{
		undo._pTable->SaveListItem(undo._row,undo._col, undo._value, UndoRef().undolist );
		undo._pTable->m_wndListCtrl.SetItemText(undo._row, undo._col, bstr_t(undo._value.c_str()));
		undo._pTable->m_wndListCtrl.InvalidateItem(undo._row, undo._col );

	}
	UndoRef().redolist.pop_back();
	return 0;
}
LRESULT CTableFormView::CUndoHandler::ExecUndo() 
{
	if(UndoRef().undolist.size() < 1)
		return 1;
	CUndo undo = UndoRef().undolist.back();

	if(undo._op == CUndo::UndeleteRow)
	{
		// FIxme: move to appropriate tab pagr
		// Re insert row that was deleted
		UndoRef().ClearRedo();
		undo._pTable->InsertListItem(undo._row, undo._mycopy.get() , UndoRef().redolist);
	}
	else if(undo._op == CUndo::UninsertRow)
	{
		UndoRef().ClearRedo();
		// Delete row that was inserted
		undo._pTable->DeleteListItem(undo._row, UndoRef().redolist);

	}
	else if(undo._op == CUndo::UnoverwriteCell)
	{
		undo._pTable->SaveListItem(undo._row,undo._col, undo._value, UndoRef().redolist );
		undo._pTable->m_wndListCtrl.SetItemText( undo._row,undo._col,bstr_t(undo._value.c_str()));
		undo._pTable->m_wndListCtrl.InvalidateItem(undo._row,undo._col );

	}
	UndoRef().undolist.pop_back();
	return 0;
}


LRESULT CTableFormView::OnUndoRedo(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(wID==ID_EDIT_UNDO) UndoRef().CUndoHandler::ExecUndo();
	else if(wID==ID_EDIT_REDO) UndoRef().CUndoHandler::ExecRedo();
	return 0;
}

void CTableFormView::InsertListItem(int n, IObject * branch , std::vector<CUndo> & list)
{
	IObjectPtr obj( creator());
	objects->insert(objects->begin() + n, obj);
	obj->Copy(branch);

	list.push_back(CUndo(CUndo::UninsertRow, this, n));

	// Listctrl
	m_wndListCtrl.InsertItem(n, "");
	FillRow(n, branch);
}

void CTableFormView::DeleteListItem(int nSelectedRow, std::vector<CUndo> & list )
{
	IObjectPtr obj( creator());
	obj->Copy(objects->at(nSelectedRow).get()); // this should keep the pointer alive till we return

	list.push_back(CUndo(CUndo::UndeleteRow, this, nSelectedRow,obj)); 

	// Listctrl
	m_wndListCtrl.DeleteItem( nSelectedRow );
	//objects->at(nSelectedRow)->Delete();  // FIXME
	IObject::Delete(objects, nSelectedRow);
}

void CTableFormView::SaveListItem(int nSelectedRow, int col, std::string value, std::vector<CUndo> & list )
{
	IObjectPtr obj( creator());
	std::string oldvalue = obj->objects()[nSelectedRow]->GetValue(col);
	list.push_back(CUndo(CUndo::UnoverwriteCell, this, nSelectedRow,col, oldvalue)); 
	obj->objects()[nSelectedRow]->SetValue(col, value);
	// We are only here because the text has already been modified.
	//m_wndListCtrl.SetItemText( nSelectedRow, col,bstr_t(value.c_str()));

}
CTableFormView::CTableFormView(std::vector<IObjectPtr> * _objects, IObject::CreatorFcn  _creator) :   creator(_creator)
{
	m_wndListCtrl.RegisterClass();
	objects = _objects; // (std::vector<IObjectPtr> *) &Resource().objects();
	copyindex=0;
	char result[ MAX_PATH ];
	std::string path( result, GetModuleFileName( NULL, result, MAX_PATH ) );
	std::string cfgfile = path.substr(0,path.find_last_of(".")) + ".ini";
	if( GetFileAttributesA(cfgfile.c_str())!= INVALID_FILE_ATTRIBUTES)
	{
		IObject::config.load( cfgfile );
	}
	mycopy = this->creator();
}

BOOL CTableFormView::PreTranslateMessage(MSG* pMsg)
{
	return CWindow::IsDialogMessage(pMsg);
}
int CTableFormView::GetSelectedItemNum()
{
	CListArray < int > aSelectedItems;
	int nSelectedRow;
	this->m_wndListCtrl.GetSelectedItems( aSelectedItems );
	if(aSelectedItems.GetSize() < 1)
		return -1;
	nSelectedRow=aSelectedItems[0];
	if(nSelectedRow < 0 || nSelectedRow>= objects->size())
		return -1;
	return nSelectedRow;

}
LRESULT CTableFormView::OnEditCopy(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(m_wndListCtrl.m_bEditItem)
	{
		if(m_wndListCtrl.m_wndItemEdit.m_hWnd!=NULL)
			::SendMessage(m_wndListCtrl.m_wndItemEdit.m_hWnd,WM_COPY,0,0);
		if(m_wndListCtrl.m_wndItemCombo.m_hWnd!=NULL)
			::SendMessage(m_wndListCtrl.m_wndItemCombo.m_hWnd,WM_COPY,0,0);
		return 0;
	}
	int nSelectedRow  = GetSelectedItemNum();
	if(nSelectedRow<0)
		return 0;

	mycopy = this->creator();
	mycopy->Copy(objects->at(nSelectedRow).get());
	return 0;
}

LRESULT CTableFormView::OnEditCut(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(m_wndListCtrl.m_bEditItem)
	{
		if(m_wndListCtrl.m_wndItemEdit.m_hWnd!=NULL)
			::SendMessage(m_wndListCtrl.m_wndItemEdit.m_hWnd,WM_CUT,0,0);
		if(m_wndListCtrl.m_wndItemCombo.m_hWnd!=NULL)
			::SendMessage(m_wndListCtrl.m_wndItemCombo.m_hWnd,WM_CUT,0,0);
		return 0;
	}

	int nSelectedRow  = GetSelectedItemNum();
	if(nSelectedRow<0)
		return 0;

	// Make pasteable copy
	mycopy = this->creator();
	mycopy->Copy(objects->at(nSelectedRow).get());

	DeleteListItem(nSelectedRow, UndoRef().undolist); 
	return 0;
}

LRESULT CTableFormView::OnEditPaste(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(m_wndListCtrl.m_bEditItem)
	{
		if(m_wndListCtrl.m_wndItemEdit.m_hWnd!=NULL)
			::SendMessage(m_wndListCtrl.m_wndItemEdit.m_hWnd,WM_PASTE,0,0);
		if(m_wndListCtrl.m_wndItemCombo.m_hWnd!=NULL)
			::SendMessage(m_wndListCtrl.m_wndItemCombo.m_hWnd,WM_PASTE,0,0);
		return 0;
	}

	// Make copy from local list "clipboard"
	IObjectPtr obj( creator());
	obj->objects().push_back(obj);
	obj->Copy(mycopy);

	InsertListItem(Tablesize()-1, obj.get(), UndoRef().undolist);
	return 0;
}
void CTableFormView::SaveRow(int nNewItem, IObject * branch)
{
	std::vector<std::string> names  = branch->GetHeaders();
	//std::vector<std::string> values  = pItem->GetValues();
	for(int k=0; k< names.size(); k++)
	{
		std::string name = names[k];
		std::string value = (LPCSTR) m_wndListCtrl.GetItemText( nNewItem, k+IMGCOLS);
		branch->SetValue(name,value);
	}
}

void CTableFormView::AddLastRow()
{		
	int nNewItem = m_wndListCtrl.AddItem("");
	m_wndListCtrl.SetItemFormat(nNewItem,0,  ITEM_FORMAT_ADDBOX,ITEM_IMAGE_ADDBOX );
	m_wndListCtrl.SetItemText( nNewItem, 0,"1");
}

void CTableFormView::FillRow(int nNewItem, IObject * branch)
{
	m_wndListCtrl.SetItemText( nNewItem, 0,"0"); 
	m_wndListCtrl.SetItemFormat(nNewItem,0,  ITEM_FORMAT_ADDBOX,ITEM_IMAGE_ADDBOX );
	//m_wndListCtrl.SetItemCheck( nNewItem, 0,0);
	//m_wndListCtrl.SetItemImage( nNewItem, 1, ITEM_IMAGE_COPY);

	std::vector<std::string> names  = branch->GetHeaders();
	std::string classname = (LPSTR) branch->GetClassname();

	//std::vector<std::string> values  = pItem->GetValues();
	for(int k=0; k< names.size(); k++)
	{
		std::string name = names[k];
		MetaType type = branch->GetType(bstr_t(name.c_str()));
		std::string value = branch->GetValue(name);
		std::string list =  IObject::config.GetSymbolValue("LIST."+classname+"."+names[k],"").c_str();
		std::string menu =  IObject::config.GetSymbolValue("MENUS."+classname+"."+names[k],"").c_str();
		std::string date =  IObject::config.GetSymbolValue("DATE."+classname+"."+names[k],"None").c_str();
		std::string selection =  IObject::config.GetSymbolValue("SELECTION."+classname+"."+names[k],"").c_str();

		CListColumn col;
		m_wndListCtrl.GetColumn(k+IMGCOLS, col );
		if(menu.size() > 0) // col.m_aComboList.GetSize()>0)
		{
			m_wndListCtrl.SetItemFormat( nNewItem, k+IMGCOLS, ITEM_FORMAT_COMBO,ITEM_FLAGS_RIGHT| ITEM_FLAGS_NONE, (CListArray<CString> &) col.m_aComboList );
			//int N = col.m_aComboList.Find(value.c_str());
			//m_wndListCtrl.SetItemComboIndex( nNewItem, k+IMGCOLS, N ); // "Item 1"		
			m_wndListCtrl.SetItemText( nNewItem, k+IMGCOLS, value.c_str() ); // "Item 1"		
		}
		else if(list.size() > 0)
		{
			CListArray < CString > aComboList;
			aComboList.Add(value.c_str());
			m_wndListCtrl.SetItemFormat(nNewItem, k+IMGCOLS, ITEM_FORMAT_COMBO, ITEM_FLAGS_RIGHT| ITEM_FLAGS_NONE, aComboList );
			//Just set the value - at initialization, use popup to distinguish selections later	
			m_wndListCtrl.SetItemText( nNewItem, k+IMGCOLS, value.c_str() ); // "Item 1"		
		}	
		else if(selection.size() > 0)
		{
			m_wndListCtrl.SetItemText( nNewItem, k+IMGCOLS, value.c_str());
			m_wndListCtrl.SetItemFormat( nNewItem, k+IMGCOLS, ITEM_FORMAT_EDIT,ITEM_FLAGS_RIGHT);
		}	
		else if(date != "None")
		{
			m_wndListCtrl.SetItemText( nNewItem, k+IMGCOLS, value.c_str());
			m_wndListCtrl.SetItemFormat( nNewItem, k+IMGCOLS, ITEM_FORMAT_DATETIME,ITEM_FLAGS_DATE_ONLY);
		}
		else
		{
			m_wndListCtrl.SetItemText( nNewItem, k+IMGCOLS, value.c_str());
			m_wndListCtrl.SetItemFormat( nNewItem, k+IMGCOLS, ITEM_FORMAT_EDIT,ITEM_FLAGS_RIGHT);
		}
	}
}
void CTableFormView::InitListColumns()
{
	// FIXME: what if no instances in branch
	std::vector<IObjectPtr> * branchObj = objects;
	std::string classname;
	std::vector<std::string> names;
	if(branchObj==NULL)
	{
		DebugBreak();
	}	

	IObjectPtr obj( creator());
	classname = (LPSTR)obj->GetClassname();
	names  = obj->GetHeaders();
	//std::vector<std::string> values  = pItem->GetValues();
	m_wndListCtrl.AddColumn( _T( "" ), 0, ITEM_IMAGE_ADDBOX /*ITEM_IMAGE_CHECKBOX*/, TRUE, ITEM_FORMAT_CHECKBOX );
	//	m_wndListCtrl.AddColumn( _T( "" ), 0, ITEM_IMAGE_COPY, TRUE, ITEM_FORMAT_CHECKBOX );
	for(int k=0; k< names.size(); k++)
	{
		std::string menu =  IObject::config.GetSymbolValue("MENUS."+classname+"."+names[k],"").c_str();
		std::string list =  IObject::config.GetSymbolValue("LIST."+classname+"."+names[k],"").c_str();
		std::string selection =  IObject::config.GetSymbolValue("SELECTION."+classname+"."+names[k],"").c_str();
		MetaType type = obj->GetType(bstr_t(names[k].c_str()));
		if(menu.size() > 0)
		{
			m_wndListCtrl.AddColumn( names[k].c_str(), 70, ITEM_IMAGE_NONE, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_RIGHT );
			CListArray < CString > aComboList;
			std::vector<std::string> items = crp::ParseFields(menu);
			for(int m=0;m<items.size(); m++)
				aComboList.Add(items[m].c_str());
			m_wndListCtrl.SetColumnFormat( k+IMGCOLS, ITEM_FORMAT_NONE, ITEM_FLAGS_RIGHT, aComboList );
		}
		else if(list.size() > 0 || selection.size() > 0)
		{
			//std::vector<std::string> items;
			m_wndListCtrl.AddColumn( names[k].c_str(), 70, ITEM_IMAGE_NONE, FALSE, ITEM_FORMAT_NONE, ITEM_FLAGS_RIGHT );
		}	
		else
		{
			m_wndListCtrl.AddColumn( names[k].c_str(), 100,ITEM_IMAGE_NONE,FALSE,ITEM_FORMAT_EDIT| LVCF_WIDTH,ITEM_FLAGS_RIGHT );
		}
	}

}
void CTableFormView::InitListItems()
{
	m_wndListCtrl.DeleteAllItems();

	std::vector<IObjectPtr> * branchObj = objects;
	std::string classname;
	std::vector<std::string> names;
	if(branchObj==NULL)
	{
		DebugBreak();
	}	

	IObjectPtr obj( creator());
	classname = (LPSTR)obj->GetClassname();
	names  = obj->GetHeaders();
	for(int j=0; j< objects->size(); j++)
	{
		int nNewItem = m_wndListCtrl.AddItem("");
		FillRow(nNewItem, objects->at(j).get());

	}
	for(int k=0; k< names.size(); k++)
	{
		MetaType type = obj->GetType(bstr_t(names[k].c_str()));
		if(type == type_is_bstr_t)
			m_wndListCtrl.AutoSizeColumn(k+IMGCOLS);
	}
	AddLastRow();

}

LRESULT CTableFormView::OnDoubleClicked( LPNMHDR lpNMHDR )
{
	CListNotify *pListNotify = reinterpret_cast<CListNotify *>( lpNMHDR );

	// + Add image
	if(pListNotify->m_nItem == (Tablesize()-1) &&  pListNotify->m_nSubItem == 0)
	{
		// FIXME: problem with zero length vector
		IObjectPtr obj( creator());
		obj->InsertFromCopy(copyindex);
		obj->Copy(obj->objects()[copyindex].get());
		// Insert before + sign
		InsertListItem(Tablesize()-1, obj.get(), UndoRef().undolist);
	}
	// - remove image
	else if(pListNotify->m_nItem>= 0 && pListNotify->m_nItem < Tablesize() &&  pListNotify->m_nSubItem == 0)
	{
		DeleteListItem(pListNotify->m_nItem, UndoRef().undolist); 
	}
	return 0;
}

LRESULT CTableFormView::OnClicked( LPNMHDR lpNMHDR )
{
	// Determine if combobox, property list list item, if so update combo, or show property dialog

	CListNotify *pListNotify = reinterpret_cast<CListNotify *>( lpNMHDR );

	std::string classname;
	std::vector<std::string> names;
	int nNewItem = pListNotify->m_nItem;
	int k = pListNotify->m_nSubItem-IMGCOLS; // skip beginning image columns
	if(k<0)
		return 0;
	// Create dummy - will be deleted after leaving this nesting
	IObjectPtr obj( creator());
	classname = (LPSTR)obj->GetClassname();
	names  = obj->GetHeaders();

	if(nNewItem<0 || nNewItem >=obj->objects().size())
		return 0;

	std::string name = names[k];
	std::string value = obj->objects()[nNewItem]->GetValue(name);
	std::string selection =  IObject::config.GetSymbolValue("SELECTION."+classname+"."+name,"").c_str();
	std::string propertylist =  IObject::config.GetSymbolValue("PROPERTY."+classname+"."+name,"None").c_str();

	if(propertylist!="None")
	{
		// parse list of name=value,name=value, 
		// No = or HTML in value ...
		CPropertiesDlg dlg(value);
		if(dlg.DoModal()==IDCANCEL)
			return 0;
		obj->objects()[nNewItem]->SetValue(name, dlg.GetNameValues());
		m_wndListCtrl.SetItemText( nNewItem, k+IMGCOLS,bstr_t(dlg.GetNameValues().c_str()));

	}
	// Selection from selection list
	if(selection.size() > 0)
	{
		std::vector<std::string> items;
		std::vector<std::string> tokens= Tokenize(selection,".");
		if(tokens.size() > 1)
			items = IObject::GetList(tokens[0], tokens[1]);
		if(items.size() == 0)
			items.push_back("");
		std::vector<std::string> selected= Tokenize(value,",");
		CSelectionDlg dlg(items,selected);
		if(dlg.DoModal()==IDCANCEL)
			return 0;
		items = dlg.GetSelectedItems();
		bstr_t bstr;
		for(int i=0; i< items.size() ; i++)
			bstr+=items[i].c_str() + bstr_t(",");
		m_wndListCtrl.SetItemText( nNewItem, k+IMGCOLS,bstr);
	}	

	return 0;
}
LRESULT CTableFormView::OnSelected( LPNMHDR lpNMHDR )
{
	CListNotify *pListNotify = reinterpret_cast<CListNotify *>( lpNMHDR );

	return 0;
}	

LRESULT CTableFormView::OnModified( LPNMHDR lpNMHDR )
{
	CListNotify *pListNotify = reinterpret_cast<CListNotify *>( lpNMHDR );

	if(pListNotify->m_nSubItem< IMGCOLS)
		return 0;
	int nNewItem = pListNotify->m_nItem;
	int k = pListNotify->m_nSubItem-IMGCOLS; // skip first two columns

	// Create dummy - will be deleted after leaving this nesting
	IObjectPtr obj( creator());
	std::string classname				= (LPSTR)obj->GetClassname();
	std::vector<std::string> names		= obj->GetHeaders();

	if(nNewItem<0 || nNewItem >=obj->objects().size())
		return 0;

	std::string name = names[k];
	std::string oldvalue = obj->GetValue(name);
	std::string value = (LPCSTR) m_wndListCtrl.GetItemText( nNewItem, k+IMGCOLS);

	if(oldvalue == value)
		return 0;

	// Only update here after modified from edit or combo ...
	//this->SaveRow(pListNotify->m_nItem, objects->at(pListNotify->m_nItem).get());
	SaveListItem(pListNotify->m_nItem, k, value, UndoRef().undolist );

	// Aftermath - if any, update other row fields based on configuration 
	std::map<std::string,std::string> updates =  IObject::config.getmap("AFTERMATH."+classname+"."+name+"."+value);
	for(std::map<std::string,std::string>::iterator it=updates.begin();it!=updates.end(); it++)
	{
		int n = obj->GetIndex ((*it).first);
		if(n<0)
			continue;
		obj->SetValue((*it).first,(*it).second);
		m_wndListCtrl.SetItemText( nNewItem, n+IMGCOLS,(*it).second.c_str() );
	}
	return 0;
}

LRESULT CTableFormView::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	m_wndListCtrl.SubclassWindow( GetDlgItem( IDC_LISTCTRL ) );
	DlgResize_Init(false);

	if ( !m_ilItemImages.CreateFromImage( IDB_LISTITEMS, 16, 0, RGB( 255, 0, 255 ), IMAGE_BITMAP, LR_CREATEDIBSECTION ) )
		return FALSE;

	LOGFONT logFont = { 0 };
	logFont.lfCharSet = DEFAULT_CHARSET;
	logFont.lfHeight = 90;
	lstrcpy( logFont.lfFaceName, _T( "New Times Roman" ) );
	logFont.lfWeight = FW_BOLD;
	logFont.lfItalic = (BYTE)TRUE;

	m_fntCustomFont1.CreatePointFontIndirect( &logFont );

	logFont.lfHeight = 100;
	lstrcpy( logFont.lfFaceName, _T( "Arial" ) );
	logFont.lfUnderline = (BYTE)TRUE;
	m_fntCustomFont2.CreatePointFontIndirect( &logFont );

	m_wndListCtrl.SetImageList( m_ilItemImages );
	m_wndListCtrl.SetFocusSubItem( TRUE );
	m_wndListCtrl.ShowHeaderSort( FALSE );

	InitListColumns();
	InitListItems();
	return TRUE;
}
LRESULT CTableFormView::OnEnterCombo( LPNMHDR lpNMHDR )
{
	std::string classname;
	std::vector<std::string> names;
	CListNotify *pListNotify = reinterpret_cast<CListNotify *>( lpNMHDR );

	int nNewItem = pListNotify->m_nItem;
	int k = pListNotify->m_nSubItem-IMGCOLS; // skip first IMGCOLS columns

	// Create dummy - will be deleted after leaving this nesting
	IObjectPtr obj( creator());
	classname = (LPSTR)obj->GetClassname();
	names  = obj->GetHeaders();

	if(nNewItem<0 || nNewItem >=obj->objects().size())
		return 0;

	std::string name = names[k];
	std::string value = obj->GetValue(name);
	std::string list =  IObject::config.GetSymbolValue("LIST."+classname+"."+name,"").c_str();
	std::string menu =  IObject::config.GetSymbolValue("MENUS."+classname+"."+name,"").c_str();

	if(list.size() > 0)
	{
		std::vector<std::string> items;
		CListArray < CString > aComboList;
		std::vector<std::string> tokens= Tokenize(list,".");
		if(tokens.size() > 1)
			items = IObject::GetList(tokens[0], tokens[1]);
		if(items.size() == 0)
			items.push_back("");
		for(int m=0;m<items.size(); m++)
			aComboList.Add(items[m].c_str());
		m_wndListCtrl.SetItemFormat(nNewItem, k+IMGCOLS, ITEM_FORMAT_COMBO, ITEM_FLAGS_RIGHT, aComboList );
	}	
	return TRUE;
}
LRESULT CTableFormView::OnPrint(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	//PrintData("");
	return 0;
}
//#include "PrintListCtrl.h"
//bool CTableFormView::PrintData(CString szPageTitle)
//{
//	CPrintListCtrl printer;
//	CListCtrl pListCtrl = this->m_wndListCtrl;
//	// Check if the data exists in the list control
//	if(pListCtrl.GetItemCount() <= 0)
//		return false;
//
//	// create the printdialog class pointer with the desired properties 
//	// and set the options to the objects 
//	CPrintDialog aPrintDlg(FALSE, 
//		PD_ALLPAGES | PD_RETURNDC, NULL);
//	aPrintDlg.m_pd.nMinPage = aPrintDlg.m_pd.nMaxPage = 1;
//	aPrintDlg.m_pd.nFromPage = aPrintDlg.m_pd.nToPage = 1;
//	// call the printer selection dialog
//	aPrintDlg.DoModal();
//	// get the HDC of the printer dialog
//	CDCHandle m_HdcPrint = aPrintDlg.GetPrinterDC();
//
//	// check for valid handle and proceed
//	if(m_HdcPrint != NULL)
//	{
//		printer.m_CurrentYPos = 0;
//		printer.m_Space = 5;
//		printer.m_GeneralFont.CreateFont(-((::GetDeviceCaps (m_HdcPrint, LOGPIXELSY)*12)/72),
//			0,0,0,FW_NORMAL,FALSE,FALSE,FALSE,DEFAULT_CHARSET,
//			OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,
//			DEFAULT_QUALITY,DEFAULT_PITCH,_T("Arial"));
//			CFont m_HeadingFont;
//			m_HeadingFont.CreateFont(-((::GetDeviceCaps (m_HdcPrint, LOGPIXELSY)*18)/72),
//				0,0,0,FW_NORMAL,FALSE,FALSE,FALSE,DEFAULT_CHARSET,
//				OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,
//				DEFAULT_QUALITY,DEFAULT_PITCH,_T("Arial"));
//		printer.m_ListFont.CreateFont(-((::GetDeviceCaps (m_HdcPrint, LOGPIXELSY)*10)/72),
//			0,0,0,FW_NORMAL,FALSE,FALSE,FALSE,DEFAULT_CHARSET,
//			OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
//			DEFAULT_QUALITY,DEFAULT_PITCH,_T("Arial"));
//		CDC m_PrintDC = this->GetDC(); // wrong
//		m_PrintDC.Attach (m_HdcPrint);
//		m_PrintDC.StartDoc(_T("Periodical List"));  
//		m_PrintDC.StartPage();
//		CRect m_PageRect; 
//		m_PageRect.left = 0;
//		m_PageRect.top = 0;
//		m_PageRect.right = ::GetDeviceCaps (m_HdcPrint, HORZRES) ;
//		m_PageRect.bottom = ::GetDeviceCaps (m_HdcPrint, VERTRES) ;
//
//		// Print the List Control heading  
//		printer.PrintListCtrlHeading(&pListCtrl, szPageTitle);
//		// Finally Print the data
//		printer.PrintListData(&pListCtrl);
//
//		m_PrintDC.EndPage();
//		m_PrintDC.EndDoc();
//		m_PrintDC.Detach();
//		delete m_PrintDC;
//		printer.m_HeadingFont.Detach();
//		printer.m_GeneralFont.Detach();
//		printer.m_ListFont.Detach();
//	}
//	else
//	{
//		return false;
//	}
//	return true;
//}