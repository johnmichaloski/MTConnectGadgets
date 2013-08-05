#pragma once

#include "Resource.h"
#include "ListCtrl.h"
#include "Config.h"


class CPrintListCtrl  
{
public:
	bool PrintData(CListCtrl* pListCtrl, CString szPageTitle);
	CPrintListCtrl();
	virtual ~CPrintListCtrl();

	// Print 
	RECT	m_PageRect;
	HDC		m_HdcPrint;
	SIZE	m_StSize;
	CFont	m_HeadingFont;
	CFont	m_ListFont;
	CFont   m_GeneralFont;
	long	m_CurrentYPos;
	long    m_RowHeight;
	CDC		*m_PrintDC;
	int		m_Space;
	int     *m_ColumnSpaces;	
	
	void PrintListCtrlHeading(CListCtrl* pListCtrl, CString szPageTitle);
	void PrintListData(CListCtrl* pListCtrl);
	int  GetColumnWidth(int theColumn, CListCtrl* pListCtrl);
	int	 GetRectangleHeight();

protected:

};

