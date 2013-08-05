//
// CMSDBuilderView.h : interface of the CCMSDBuilderView class
//

#pragma once
#include <string>
#include <algorithm>
#include <vector>


#define ID_NOTIFY_COPY  WM_APP + 3
#define ID_NOTIFY_DATAUPDATE  WM_APP + 4




template <class T>
class CCMSDBuilderViewT : public CWindowImpl<CCMSDBuilderViewT<T>, CTreeViewCtrl, CControlWinTraits>
{
public:
   typedef CWindowImpl< CCMSDBuilderViewT<T>, CTreeViewCtrl, CControlWinTraits > parentClass;

	CCMSDBuilderViewT<T>() 
	{
		m_hMyRoot=NULL;
	}
	CImageList m_ImageSmall;
	DECLARE_WND_SUPERCLASS(NULL, CTreeViewCtrl::GetWndClassName())

	CTreeItem                                                   m_hMyRoot;

	BOOL PreTranslateMessage(MSG* pMsg);
	BOOL OnRedraw();
	BOOL Clear();
	void DeleteChildren(HTREEITEM hmyItem);
	BOOL IsExpanded(HTREEITEM hItem);
	CString ItemToObject(HTREEITEM hItem) const;
	int NumberOfChildItems(HTREEITEM hItem);
	void CollapseExpandBranch( HTREEITEM hti, int nAction);
	void Collapseall() ;
	void Expandall() ;
	void OnExpand() ;
	void OnCollapse() ;
	BEGIN_MSG_MAP(CCMSDBuilderViewT<T>)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
        //MESSAGE_HANDLER(WM_CONTEXTMENU, OnContextMenu)
		MESSAGE_HANDLER(WM_RBUTTONDOWN, OnMouseRightClick)
		REFLECTED_NOTIFY_CODE_HANDLER(TVN_SELCHANGED, OnSelectionChanged )
     DEFAULT_REFLECTION_HANDLER()
	END_MSG_MAP()
	
	LRESULT OnSelectionChanged(int /*idCtrl*/, LPNMHDR pnmh, BOOL& /*bHandled*/)
	{
		return 0;
	}

	// This is for control not view
	BOOL SubclassWindow(HWND hWnd)
	{
		ATLASSERT(m_hWnd==NULL);
		ATLASSERT(::IsWindow(hWnd));
		BOOL bRet = parentClass::SubclassWindow(hWnd);
		// if( bRet ) _Init();
		return bRet;
	}
    LRESULT OnContextMenu(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
   {
          MessageBox ("WM_CONTEXTMENU", "!"); 
    //if( m_list.GetItemPidl(m_list.GetSelectedIndex(), &pidl)==FALSE ) return 0;
      //m_menu.TrackPopupMenu(pidl, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), m_hWnd);
      return 0;
   }
	LRESULT OnMouseRightClick(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& bHandled)
	{
		CPoint pt(LOWORD(lParam), HIWORD(lParam));
		::ClientToScreen(m_hWnd, &pt) ;

		UINT Flags = 0;
		UINT id;
		HTREEITEM h_item = NULL ;
		TVHITTESTINFO tv_ht ;
		TVITEM tv ;
		ZeroMemory(&tv, sizeof(TVITEM)) ;
		ZeroMemory(&tv_ht, sizeof(TVHITTESTINFO)) ;
		::GetCursorPos(&(tv_ht.pt)) ;
		::ScreenToClient(m_hWnd, &(tv_ht.pt)) ;
		tv_ht.flags = TVHT_ONITEM ;
		h_item = (HTREEITEM)SendMessage(m_hWnd, TVM_HITTEST, 0, (LPARAM)&tv_ht) ;
		if(h_item==0)
			return 0;
		TVITEM tvitem;
		tvitem.hItem = h_item;
		tvitem.mask = TVIF_IMAGE | TVIF_HANDLE ;
		GetItem(&tvitem);	

		// Create Menu
		//
		CMenu m_menu;
		m_menu.CreatePopupMenu();


		m_menu.AppendMenu(MF_STRING, ID_NOTIFY_COPY, "Copy" );
		m_menu.AppendMenu(MF_STRING, ID_NOTIFY_DATAUPDATE, "Update" );

		Flags =  TPM_CENTERALIGN | TPM_RIGHTBUTTON |TPM_RETURNCMD ; //| TPM_NONOTIFY;
		CMenuHandle menu  = m_menu; 
		id=menu.TrackPopupMenu(Flags,pt.x,pt.y, m_hWnd);
		if(id==ID_NOTIFY_COPY) 
		{
			Copy((T * ) GetItemData(h_item)); 
		}

		InvalidateRect(NULL, FALSE);
		return 0;
	}
	// Handler prototypes (uncomment arguments if needed):
	//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)
	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	HTREEITEM InsertFileItem(HTREEITEM hParent, T* pItem, std::string text, BOOL bShared, int nIcon, int nSelIcon, BOOL bCheckForChildren){ throw "InsertFileItem not implemented"; return NULL;}
	void PopulateTree();
	virtual void Copy(T *) { }
};

struct CTreeNode
{
	typedef enum  Type { root, branch, instance, node};
	CTreeNode(IObject * _object, bstr_t _name, Type _type) 
		:  object(_object), name(_name),  type (_type){}
	IObjectPtr object;
	bstr_t name;
	Type type;
};

class CCMSDBuilderView : public CCMSDBuilderViewT<CTreeNode>
{
public:
	CTreeItem resources;
	CTreeItem cells;
	CTreeItem parts;
	CTreeItem jobs;
	CTreeItem distributions;
	CTreeItem calendars;
	CTreeItem layouts;
	HTREEITEM InsertFileItem(HTREEITEM hParent, CTreeNode * pItem, std::string text, BOOL bShared, int nIcon, int nSelIcon, BOOL bCheckForChildren);
	void PopulateTree(CCMSDIntegrator *);
	virtual void Copy(CTreeNode * node) 
	{ 
		CopyClipboard(node->name);
	}

};
#if 0
const UINT WM_POPULATE_TREE = WM_APP + 1;
const UINT WM_ITEM_SELECTED = WM_APP + 2;

class CSystemImageList
{
public:
	CSystemImageList();
	~CSystemImageList();

	//Methods
	CImageList* GetImageList();

protected:
	CImageList m_ImageList;
	static int m_nRefCount;
};

class CCMSDBuilderView : public CWindowImpl< CCMSDBuilderView, CTreeViewCtrl>			                   
{
public:
	CCMSDBuilderView::CCMSDBuilderView()
	{
		m_bShowFiles		= TRUE;
		m_hSelItem			= NULL;
	}

	virtual ~CCMSDBuilderView(){};
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL SubclassWindow( HWND hWnd );

	// Public methods
	void		SetRootFolder( const std::string sPath );
	std::string GetRootFolder() const { return m_sRootFolder; };
	std::string	ItemToPath( HTREEITEM hItem );
	std::string	GetSelectedPath();
	HTREEITEM	SetSelectedPath( const std::string sPath, BOOL bExpanded = FALSE );
	void		SetShowFiles( BOOL bFiles );
	BOOL		GetShowFiles() const { return m_bShowFiles; };

	BEGIN_MSG_MAP(CCMSDBuilderView)
		MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDblClick)
		MESSAGE_HANDLER(WM_POPULATE_TREE, OnPopulateTree)
		REFLECTED_NOTIFY_CODE_HANDLER(TVN_ITEMEXPANDING, OnItemExpanding )
		DEFAULT_REFLECTION_HANDLER()
	END_MSG_MAP()

	LRESULT OnLButtonDblClick(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnPopulateTree(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnItemExpanding(int /*idCtrl*/, LPNMHDR pnmh, BOOL& /*bHandled*/);

	void OnViewRefresh();

protected:

	void      DisplayPath( const std::string sPath, HTREEITEM hParent, BOOL bUseSetRedraw = TRUE );
	void      DisplayDrives( HTREEITEM hParent, BOOL bUseSetRedraw = TRUE );
	int       GetIconIndex( const std::string sFilename );
	int       GetIconIndex( HTREEITEM hItem );
	int       GetSelIconIndex( const std::string sFilename );
	int       GetSelIconIndex( HTREEITEM hItem );
	BOOL      HasGotSubEntries( const std::string sDirectory );
	HTREEITEM InsertFileItem( const std::string sFile, const std::string sPath, HTREEITEM hParent );
	HTREEITEM FindSibling( HTREEITEM hParent, const std::string sItem );
	static int CompareByFilenameNoCase( std::string element1, std::string element2 );

	CSystemImageList m_SysImageList;
	std::string      m_sRootFolder;
	BOOL             m_bShowFiles;
	HTREEITEM        m_hSelItem;
};
#endif


template <class T>
BOOL CCMSDBuilderViewT<T>::PreTranslateMessage(MSG* pMsg)
{
	if((pMsg->message < WM_KEYFIRST || pMsg->message > WM_KEYLAST) &&
	   (pMsg->message < WM_MOUSEFIRST || pMsg->message > WM_MOUSELAST))
		return FALSE;

	// give HTML page a chance to translate this message
	return (BOOL)SendMessage(WM_FORWARDMSG, 0, (LPARAM)pMsg);
}
template <class T>
LRESULT CCMSDBuilderViewT<T>::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
	bHandled=false;
	return 1;
}
template <class T>
void CCMSDBuilderViewT<T>::CollapseExpandBranch( HTREEITEM hti, int nAction)
{
	if (ItemHasChildren(hti))
	{
		Expand(hti, nAction);
		hti = GetChildItem(hti);                
		while (hti)
		{
			CollapseExpandBranch(hti, nAction);
			hti = GetNextSiblingItem(hti);
		}
	}
}

template <class T>
void CCMSDBuilderViewT<T>::Collapseall() 
{
	HTREEITEM hti = GetRootItem();        
	while (hti)
	{
		CollapseExpandBranch(hti, TVE_COLLAPSE);
		hti = GetNextSiblingItem(hti);
	}   
}

template <class T>
void CCMSDBuilderViewT<T>::Expandall() 
{
	HTREEITEM hti = GetRootItem();        
	while (hti)
	{
		CollapseExpandBranch(hti, TVE_EXPAND);
		hti = GetNextSiblingItem(hti);
	}
}

template <class T>
void CCMSDBuilderViewT<T>::OnExpand() 
{
	HTREEITEM hti = GetSelectedItem();        
	while (hti)
	{
		CollapseExpandBranch(hti, TVE_EXPAND);
		hti = GetNextSiblingItem(hti);
	}
}

template <class T>
void CCMSDBuilderViewT<T>::OnCollapse() 
{
	HTREEITEM hti = GetSelectedItem();        
	while (hti)
	{
		CollapseExpandBranch(hti,TVE_COLLAPSE );
		hti = GetNextSiblingItem(hti);
	}
}

template <class T>
void CCMSDBuilderViewT<T>::DeleteChildren(HTREEITEM hmyItem)
{
	// Delete all of the children of hmyItem.
	if (ItemHasChildren(hmyItem))
	{
		HTREEITEM hNextItem;
		HTREEITEM hChildItem = GetChildItem(hmyItem);

		while (hChildItem != NULL)
		{
			hNextItem = GetNextItem(hChildItem, TVGN_NEXT);
			DeleteItem(hChildItem);
			hChildItem = hNextItem;
		}
	}
}
template <class T>
BOOL CCMSDBuilderViewT<T>::IsExpanded(HTREEITEM hItem)
{
	TVITEM tvItem;
	tvItem.hItem = hItem;
	tvItem.mask = TVIF_HANDLE | TVIF_STATE;
	return GetItem(&tvItem) && (tvItem.state & TVIS_EXPANDED);
}
template <class T>
BOOL CCMSDBuilderViewT<T>::Clear()
{
	HTREEITEM hitem = this->GetSelectedItem();
	if(hitem==NULL)
		return false;

	//Delete all the items
	//DeleteAllItems();

	// Delete all children not item
	DeleteChildren(hitem);
	return true;
}
template <class T>
int CCMSDBuilderViewT<T>::NumberOfChildItems(HTREEITEM hItem)
{
	int nChildren = 0;
	HTREEITEM hChild = GetChildItem(hItem);
	while (hChild)
	{
		++nChildren;
		hChild = GetNextSiblingItem(hChild);
	}
	return nChildren;
}
template <class T>
CString CCMSDBuilderViewT<T>::ItemToObject(HTREEITEM hItem) const
{
	CString sPath;
	if (hItem)
	{
		//CTreeFileCtrlItemInfo* pItem = (CTreeFileCtrlItemInfo*) GetItemData(hItem);
		//ASSERT(pItem);
		//sPath = pItem->m_sFQPath;
	}
	//return sPath;
	return "";
}
template <class T>
BOOL CCMSDBuilderViewT<T>::OnRedraw()
{

	CString sItem;
	bool bExpanded;
	HTREEITEM hSelItem;
	int nIcon=1;
	int nSelIcon=1;

	CWaitCursor wait;
	SetRedraw(FALSE);
//Get the item which is currently selected
	hSelItem = GetSelectedItem();

	bExpanded = FALSE;
	if (hSelItem)
	{
		sItem = ItemToObject(hSelItem);
		bExpanded = IsExpanded(hSelItem); 
	}


	//Reselect the initially selected item
	//if (hSelItem)
	//	SetSelectedPath(sItem, bExpanded);

	//Turn back on the redraw flag
	SetRedraw(TRUE);
	return true;
}
