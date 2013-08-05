// CMSDBuilderView.cpp : implementation of the CCMSDBuilderView class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

#include "CMSDBuilderView.h"


HTREEITEM CCMSDBuilderView::InsertFileItem(HTREEITEM hParent, CTreeNode * pItem, std::string text, BOOL bShared, int nIcon, int nSelIcon, BOOL bChildren)
{

	HTREEITEM hItem ;
	TV_INSERTSTRUCT tvis;


	//Add the actual item
	ZeroMemory(&tvis, sizeof(TV_INSERTSTRUCT));
	tvis.hParent = hParent;
	tvis.hInsertAfter = TVI_LAST;
	tvis.item.mask = TVIF_CHILDREN | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT | TVIF_PARAM;
	tvis.item.lParam = (LPARAM) pItem;
	tvis.item.pszText = const_cast<char *>(text.c_str()); // sLabel.GetBuffer(sLabel.GetLength());
	tvis.item.iImage = nIcon;
	tvis.item.iSelectedImage = nSelIcon;
	tvis.item.cChildren = bChildren;
	if (bShared)
	{
		tvis.item.mask |= TVIF_STATE;
		tvis.item.stateMask |= TVIS_OVERLAYMASK;
		tvis.item.state |= INDEXTOOVERLAYMASK(1); //1 is the index for the shared overlay image
	}

	hItem = InsertItem(&tvis);
	return hItem;
}

void CCMSDBuilderView::PopulateTree(CCMSDIntegrator * xml)
{

	//attach the image list to the tree control
	//SetImageList(&theSystemImageList.m_ImageList, TVSIL_NORMAL);
	bool bFail = m_ImageSmall.Create (16, 15, ILC_COLOR32|ILC_MASK, 2, 1);
	// Add my bitmap, make all red pixels transparent.
	CBitmap bm;
	bm.LoadBitmap(IDB_TREEBITMAP);
	if(m_ImageSmall.Add(bm, RGB(255, 0, 0))<0)
		OutputDebugString("m_ImageSmall.Add Failed\n");
	CImageList i   = SetImageList(m_ImageSmall.Detach(), TVSIL_NORMAL);
	//Force a refresh

	m_hMyRoot = InsertItem(_T("CMSD"), 0, 0, TVI_ROOT, NULL);
	std::vector<IObjectPtr> * branches[]  = { (std::vector<IObjectPtr> *) &Resource().objects(), 
		(std::vector<IObjectPtr> *) &Cell().objects(), 
		(std::vector<IObjectPtr> *) &Part().objects(),
		(std::vector<IObjectPtr> *) &ProcessPlan().objects(),
		(std::vector<IObjectPtr> *) &Job().objects(),
		(std::vector<IObjectPtr> *) &Distribution().objects(),
		(std::vector<IObjectPtr> *) &Calendar().objects(),
		(std::vector<IObjectPtr> *)&Layout().objects(),
	};

	for(int i=0; i< sizeof(branches)/sizeof(std::vector<IObjectPtr> *); i++)
	{
		// FIXME: what if no instances in branch
		std::vector<IObjectPtr> * branchObj = branches[i];
		if(branchObj==NULL)
		{
			DebugBreak();
		}
		std::string classname = (LPSTR) branchObj->at(0)->GetClassname();
		CTreeNode *node = new CTreeNode(branches[i]->at(0).get(), classname.c_str(), CTreeNode::branch);
		CTreeItem branch =		InsertFileItem(m_hMyRoot, node, classname, FALSE, 1, 1, TRUE);

		for(int j=0; j< branches[i]->size(); j++)
		{
			std::string id = branches[i]->at(j)->GetValue("identifier");
			//CTreeItem hItem = InsertItem(id.c_str(), 2, 2, branch, NULL);
			CTreeNode *node = new CTreeNode(branches[i]->at(j).get(), id.c_str(), CTreeNode::instance);
			CTreeItem instance = InsertFileItem(branch,  node, id, FALSE, 2, 2, TRUE);

			std::vector<std::string> names  = branches[i]->at(j)->GetHeaders();
			//std::vector<std::string> values  = pItem->GetValues();
			for(int k=0; k< names.size(); k++)
			{
				node = new CTreeNode(branches[i]->at(j).get(), names[k].c_str(), CTreeNode::node);
				InsertFileItem(instance,  node, names[k], FALSE, 3, 3, FALSE);
			}
		}
	}
	this->Expand(m_hMyRoot);
	OnRedraw();
}

