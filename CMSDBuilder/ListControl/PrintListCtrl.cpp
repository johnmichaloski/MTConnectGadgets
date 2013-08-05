// PrintListCtrl.cpp: implementation of the CPrintListCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PrintListCtrl.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPrintListCtrl::CPrintListCtrl()
{

}

CPrintListCtrl::~CPrintListCtrl()
{

}

bool CPrintListCtrl::PrintData(CListCtrl* pListCtrl, CString szPageTitle)
{
	if(pListCtrl->GetItemCount() <= 0)
		return false;
	
	CPrintDialog *aPrintDlg = new CPrintDialog(FALSE, PD_ALLPAGES | PD_RETURNDC, NULL);
	aPrintDlg->m_pd.nMinPage = aPrintDlg->m_pd.nMaxPage = 1;
	aPrintDlg->m_pd.nFromPage = aPrintDlg->m_pd.nToPage = 1;
	aPrintDlg->DoModal();
	m_HdcPrint = aPrintDlg->GetPrinterDC();

	if(m_HdcPrint != NULL)
	{
		m_CurrentYPos = 130;
		m_Space = 5;
		m_GeneralFont.CreateFont(-((::GetDeviceCaps (m_HdcPrint, LOGPIXELSY)*12)/72),0,0,0,FW_NORMAL,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,_T("Arial"));
		m_HeadingFont.CreateFont(-((::GetDeviceCaps (m_HdcPrint, LOGPIXELSY)*18)/72),0,0,0,FW_NORMAL,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,_T("Arial"));
		m_ListFont.CreateFont(-((::GetDeviceCaps (m_HdcPrint, LOGPIXELSY)*10)/72),0,0,0,FW_NORMAL,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,_T("Arial"));
		m_PrintDC = new CDC;
		m_PrintDC->Attach (m_HdcPrint);    
		m_PrintDC->StartDoc(_T("Periodical List"));  
		m_PrintDC->StartPage();
		m_PageRect.left = 0;
		m_PageRect.top = 0;
		m_PageRect.right = ::GetDeviceCaps (m_HdcPrint, HORZRES) ;
		m_PageRect.bottom = ::GetDeviceCaps (m_HdcPrint, VERTRES) ;

		PrintListCtrlHeading(pListCtrl, szPageTitle);
		PrintListData(pListCtrl);

		m_PrintDC->EndPage();
		m_PrintDC->EndDoc();
		m_PrintDC->Detach();
		delete m_PrintDC;
		m_HeadingFont.Detach();
		m_GeneralFont.Detach();
		m_ListFont.Detach();
	}
	else
	{
		delete aPrintDlg;
		return false;
	}
	delete aPrintDlg;
	return true;
}

int CPrintListCtrl::GetColumnWidth(int theColumn, CListCtrl* pListCtrl)
{
	int aMaxLen = 0;
	HDITEM  aStHDI;
	TCHAR   aSzBuf[255];

	aStHDI.mask       = HDI_TEXT;
    aStHDI.pszText    = aSzBuf;
    aStHDI.cchTextMax = sizeof(aSzBuf);
	
	m_PrintDC->SelectFont(m_GeneralFont);
	pListCtrl->GetHeaderCtrl()->GetItem(theColumn,&aStHDI);
	GetTextExtentPoint32(m_PrintDC->m_hDC, aStHDI.pszText, _tcslen(aStHDI.pszText), &m_StSize);
	if(m_StSize.cx > aMaxLen)
		aMaxLen = m_StSize.cx;
	
	for(int aLine = 0; aLine<pListCtrl->GetItemCount(); aLine++)
	{
		m_PrintDC->SelectObject(m_ListFont);
		int aLen = pListCtrl->GetItemText(aLine,theColumn,aSzBuf,sizeof(aSzBuf));
		if(aLen <=0 )
			_tcscpy(aSzBuf,_T("E"));
		GetTextExtentPoint32(m_PrintDC->m_hDC, aSzBuf, _tcslen(aSzBuf), &m_StSize);
		if(m_StSize.cx > aMaxLen)
			aMaxLen = m_StSize.cx;
	}
	return aMaxLen+30;
}

int CPrintListCtrl::GetRectangleHeight()
{
	int aLength=130;
	CString aStrBuffer = _T("Width");
	m_PrintDC->SelectObject(&m_HeadingFont);
	GetTextExtentPoint32(m_PrintDC->m_hDC, aStrBuffer.GetBuffer(0), _tcslen(aStrBuffer.GetBuffer(0)), &m_StSize);
	aLength = aLength + m_Space + m_StSize.cy;
	m_PrintDC->SelectObject(&m_GeneralFont);
	GetTextExtentPoint32(m_PrintDC->m_hDC, aStrBuffer.GetBuffer(0), _tcslen(aStrBuffer.GetBuffer(0)), &m_StSize);
	aLength = aLength + m_Space + m_StSize.cy + m_Space;
	return aLength;
}

void CPrintListCtrl::PrintListCtrlHeading(CListCtrl* pListCtrl, CString szPageTitle)
{
	long aEndYPos = GetRectangleHeight();
	CString aStrBuffer = szPageTitle;

	m_CurrentYPos = aEndYPos + (m_Space*3);

	RECT aRect;
	int aCurrentHPos = 50;
	int aMaxColumnLen = 0;
	CBrush aBrush;
	aBrush.CreateSolidBrush(RGB(220,220,220));
	m_ColumnSpaces = new int[pListCtrl->GetHeaderCtrl()->GetItemCount()];	

	m_PrintDC->SetTextColor(RGB(114,106,16));
	m_PrintDC->SetBkMode(TRANSPARENT);
	for(int aColumn=0; aColumn<pListCtrl->GetHeaderCtrl()->GetItemCount(); aColumn++)
	{
		HDITEM  aStHDI;
		TCHAR   aSzBuf[255];

		aStHDI.mask       = HDI_TEXT;
		aStHDI.pszText    = aSzBuf;
		aStHDI.cchTextMax = sizeof(aSzBuf);

		aMaxColumnLen = GetColumnWidth(aColumn,pListCtrl);
		m_ColumnSpaces[aColumn] = aMaxColumnLen;

		aRect.left = aCurrentHPos;
		aRect.top = m_CurrentYPos;
		aRect.right = aCurrentHPos+aMaxColumnLen+(m_Space*2);
		aRect.bottom = m_CurrentYPos+m_StSize.cy+(m_Space*4);

		m_PrintDC->Rectangle(&aRect);		
		
		aRect.left = aCurrentHPos + 2;
		aRect.top = m_CurrentYPos + 2;
		aRect.right = aCurrentHPos+aMaxColumnLen+(m_Space*2)-2;
		aRect.bottom = m_CurrentYPos+m_StSize.cy+(m_Space*4)-2;

		m_PrintDC->FillRect(&aRect,&aBrush);

		aRect.left = aCurrentHPos+m_Space;
		aRect.top = m_CurrentYPos+m_Space;
		aRect.right = aCurrentHPos+aMaxColumnLen+m_Space;
		aRect.bottom = m_CurrentYPos+m_StSize.cy+(m_Space*2);
		
		pListCtrl->GetHeaderCtrl()->GetItem(aColumn,&aStHDI);

		m_PrintDC->SelectObject(m_ListFont);		
		m_PrintDC->DrawText(aStHDI.pszText,&aRect,DT_SINGLELINE | DT_CENTER);
		aCurrentHPos = aRect.right+m_Space;
	}
	m_CurrentYPos = aRect.bottom+(m_Space*2);	

	aRect.top = 130;
	aRect.left = 50;
	aRect.right = aCurrentHPos;
	aRect.bottom = aEndYPos;
	
	m_PrintDC->Rectangle(&aRect);
	m_PrintDC->SelectObject(&m_HeadingFont);

	GetTextExtentPoint32(m_PrintDC->m_hDC, aStrBuffer.GetBuffer(0), _tcslen(aStrBuffer.GetBuffer(0)), &m_StSize);

	aRect.top = 150+m_Space;
	aRect.left = 50;
	aRect.right = aCurrentHPos;
	aRect.bottom = 150 +m_Space+m_StSize.cy;

	m_PrintDC->SetTextColor(RGB(0,0,255));
	m_PrintDC->DrawText(aStrBuffer,&aRect,DT_SINGLELINE | DT_CENTER);
}

void CPrintListCtrl::PrintListData(CListCtrl* pListCtrl)
{
	m_PrintDC->SelectObject(m_ListFont);
	m_PrintDC->SetTextColor(RGB(0,0,0));
	
	for(int aRow=0;aRow<pListCtrl->GetItemCount();aRow++)
	{
		RECT  aRect;
		int aCurrentHPos = 50;
		if((m_CurrentYPos+m_StSize.cy+(m_Space*4)) > m_PageRect.bottom)
		{				
			m_PrintDC->EndPage(); 
			m_PrintDC->StartPage();
			m_CurrentYPos = 130;
		}

		for(int aColumn=0; aColumn<pListCtrl->GetHeaderCtrl()->GetItemCount(); aColumn++)
		{
			aRect.left = aCurrentHPos;
			aRect.top = m_CurrentYPos;
			aRect.right = aCurrentHPos+m_ColumnSpaces[aColumn]+(m_Space*2);
			aRect.bottom = m_CurrentYPos+m_StSize.cy+(m_Space*4);
		
			m_PrintDC->Rectangle(&aRect);

			aRect.left = aCurrentHPos+m_Space;
			aRect.top =  m_CurrentYPos+m_Space;
			aRect.right = aCurrentHPos+m_ColumnSpaces[aColumn]+m_Space;
			aRect.bottom = m_CurrentYPos+m_StSize.cy+(m_Space*2);

			m_PrintDC->DrawText(pListCtrl->GetItemText(aRow,aColumn),&aRect,DT_SINGLELINE | DT_LEFT);
			aCurrentHPos = aRect.right + m_Space;
		}
		m_CurrentYPos = aRect.bottom + (m_Space*2);
	}
}