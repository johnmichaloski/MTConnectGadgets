//
// CMSDCommandCellView.cpp : implementation of the CCMSDCommandCellView class
//

#include "stdafx.h"
#include "resource.h"

#include "CMSDCommandCellView.h"
#include "AgentCfg.h"

#define CHECKCOL 0
#define TAGCOL  1
#define VALUECOL  2



BOOL CCMSDCommandCellView::PreTranslateMessage(MSG* pMsg)
{
	return CWindow::IsDialogMessage(pMsg);
}


LRESULT CCMSDCommandCellView::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	if ( !m_ilItemImages.CreateFromImage( IDB_LISTITEMS, 16, 0, RGB( 255, 0, 255 ), IMAGE_BITMAP, LR_CREATEDIBSECTION ) )
		return FALSE;
	m_wndListCtrl.SubclassWindow( GetDlgItem( IDC_LISTCTRL ) );
	_devicetype=this->GetDlgItem(IDC_DEVICENAME);
	_socketnumber=this->GetDlgItem(IDC_DEVICENAME2);
	_ipaddress=this->GetDlgItem(IDC_IPEDIT);
	_ipport=this->GetDlgItem(IDC_PORTEDIT);
	
	return 0;
}

void CCMSDCommandCellView::FillRow(int nNewItem, MTConnectDataModel::iterator it )
{
	// Row i
	m_wndListCtrl.SetItemText( nNewItem, 0, "0"); 
	m_wndListCtrl.SetItemFormat(nNewItem,0,  ITEM_FORMAT_ADDBOX,ITEM_IMAGE_ADDBOX );
	m_wndListCtrl.SetItemCheck(nNewItem, 0, 1 );

//	m_wndListCtrl.SetItemFormat( nNewItem, DEVICECOL, ITEM_FORMAT_COMBO,ITEM_FLAGS_RIGHT| ITEM_FLAGS_NONE, (CListArray<CString> &) allDevicesComboList);
	m_wndListCtrl.SetItemFormat( nNewItem, TAGCOL, ITEM_FORMAT_NONE, ITEM_FLAGS_LEFT );
	m_wndListCtrl.SetItemText( nNewItem, TAGCOL,(*it).first.c_str());
	CDataItem	 d;
	m_wndListCtrl.SetItemFormat( nNewItem, VALUECOL, ITEM_FORMAT_EDIT, ITEM_FLAGS_RIGHT );
	if(GetDataItem( (*it).first, d) && d.type == "ASSET_CHANGED")
	{
		m_wndListCtrl.SetItemFormat( nNewItem, VALUECOL, ITEM_FORMAT_NONE, ITEM_FLAGS_RIGHT );
		m_wndListCtrl.SetItemText( nNewItem, VALUECOL,"...");
	}
}

void CCMSDCommandCellView::InitBasicList()
{
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

	//m_wndListCtrl.AddColumn( _T( "" ), 0, ITEM_IMAGE_CHECKBOX, TRUE, ITEM_FORMAT_CHECKBOX );
	m_wndListCtrl.AddColumn( _T( "" ), 0, ITEM_IMAGE_ADDBOX /*ITEM_IMAGE_CHECKBOX*/, TRUE, ITEM_FORMAT_CHECKBOX );

	m_wndListCtrl.AddColumn( _T( "Tag" ), 100,ITEM_IMAGE_NONE,FALSE,ITEM_FORMAT_EDIT| LVCF_WIDTH,ITEM_FLAGS_LEFT );
	m_wndListCtrl.AddColumn( _T( "Value" ), 100,ITEM_IMAGE_NONE,FALSE,ITEM_FORMAT_EDIT| LVCF_WIDTH,ITEM_FLAGS_CENTRE );

	//m_wndListCtrl.AddColumn( _T( "Progress" ), 170, ITEM_IMAGE_ATTACHMENT, FALSE, ITEM_FORMAT_PROGRESS );
	m_wndListCtrl.ShowHeaderSort( FALSE );
	//for(DataDictionary::iterator it  = Dict().begin(); it!= Dict().end(); it++)
	for(MTConnectDataModel::iterator it  = DataModel().begin(); it!= DataModel().end(); it++)
	{
		int nNewItem = m_wndListCtrl.AddItem("");
		FillRow( nNewItem,it);
	}
	AddLastRow();
#if 0
	for(int i=0; i<  Tablesize(); i++)
	{
		int nNewItem = m_wndListCtrl.AddItem("");
		FillRow( nNewItem);
	}
	AddLastRow();
#endif
}
void CCMSDCommandCellView::AddLastRow()
{		
	int nNewItem = m_wndListCtrl.AddItem("");
	m_wndListCtrl.SetItemFormat(nNewItem,0,  ITEM_FORMAT_ADDBOX,ITEM_IMAGE_ADDBOX );
	m_wndListCtrl.SetItemText( nNewItem, 0,"1");
	for(int i=1; i< m_wndListCtrl. GetColumnCount(); i++)
	{
		m_wndListCtrl.SetItemFormat(nNewItem,i,  ITEM_FORMAT_EDIT,ITEM_FLAGS_READ_ONLY );
		m_wndListCtrl.SetItemText( nNewItem, i, _T( "" ));
	}
}
void CCMSDCommandCellView::Update()
{
	int i;
	for(i=0; i< Tablesize() -1 ; i++)
	{
		std::string tag,value;
		tag = (LPCSTR) m_wndListCtrl.GetItemText(i,TAGCOL);
		if(tag.empty()) 
			continue;
		value = (LPCSTR) m_wndListCtrl.GetItemText(i,VALUECOL);
		if(value=="...")
			continue;
		if(!value.empty())
		{
			std::string type = _shdr. GetType( tag);
			_shdr.StoreValue( tag, value, type);
		}
	}

	CString iptext;
	_ipaddress.GetWindowText(iptext);
	_devicesAgentCfg->UpdateDevice(_shdr.DeviceName(),"",(LPCSTR) iptext);
	_ipport.GetWindowText(iptext);
	_devicesAgentCfg->UpdateDevice(_shdr.DeviceName(),(LPCSTR) iptext,"");

}
LRESULT CCMSDCommandCellView::OnBnClickedButton2(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	Update();
	return 0;
}

LRESULT CCMSDCommandCellView::OnDoubleClicked( LPNMHDR lpNMHDR )
{
	CListNotify *pListNotify = reinterpret_cast<CListNotify *>( lpNMHDR );
	// + Add image
	// - remove image
	if(pListNotify->m_nItem>= 0 && pListNotify->m_nItem < Tablesize() &&  pListNotify->m_nSubItem == VALUECOL)
	{
		CString tag =m_wndListCtrl.GetItemText(pListNotify->m_nItem,TAGCOL);
		CDataItem	 d;
		if(GetDataItem((LPCSTR) tag, d) && d.type == "ASSET_CHANGED")
		{
			static TCHAR strFilter[] = _T("All Files (*.*)\0*.*\0");
			CFileDialog fileDlg(TRUE,
				_T("*"),
				NULL,
				OFN_HIDEREADONLY,
				strFilter);			
			if( fileDlg.DoModal ()!=IDOK )
				return 0;
			m_wndListCtrl.SetItemText( pListNotify->m_nItem, VALUECOL,fileDlg.m_szFileName);
		}
	}
	return 0;
}	

int CCMSDCommandCellView::GetRowNumber(std::string item)
{
	for(int i=1; i< Tablesize(); i++)
	{
		std::string tag;
		tag = (LPCSTR) m_wndListCtrl.GetItemText(i,TAGCOL);
		if(tag==item)
			return i;
	}
	return -1;
}


LRESULT CCMSDCommandCellView::OnBnClickedButton1(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	static char * progs[] ={ "CIRCMIL.NC", "CDS.NC", "BRACKET.NC", "BODYJOINT.NC" };
	static char * partids[] ={ "NIST1234", "NIST1235", "NIST1236", "NIST1237" };
	static char * partcnts[] ={ "1", "5", "2", "1" };
	static char * time[] ={ "10", "50", "20", "180" };
	static int n=0;
	int i;

	i = GetRowNumber("command");
	if(i>0)	m_wndListCtrl.SetItemText( i, VALUECOL,"RUN");
	i = GetRowNumber("cmdnum");
	if(i>0)	m_wndListCtrl.SetItemText( i, VALUECOL,StdStringFormat("%d",n).c_str());

	i = GetRowNumber("program");
	if(i>0)	m_wndListCtrl.SetItemText( i, VALUECOL,progs[n%4]);
	i = GetRowNumber("partid");
	if(i>0)	m_wndListCtrl.SetItemText( i, VALUECOL,partids[n%4]);
	i = GetRowNumber("partcount");
	if(i>0)	m_wndListCtrl.SetItemText( i, VALUECOL,partcnts[n%4]);
	i = GetRowNumber("estimatedCompletion");
	if(i>0)	m_wndListCtrl.SetItemText( i, VALUECOL,time[n%4]);
	n++;

	m_wndListCtrl.Invalidate();
	Update();


	return 0;
}
