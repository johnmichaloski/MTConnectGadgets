// CmdEdit.cpp : implementation file
//

#include "stdafx.h"
#include "CmdEdit.h"

/////////////////////////////////////////////////////////////////////////////
// CCmdEdit

CCmdEdit::CCmdEdit()
{
	m_pConsumer = new CSpawnConsumer1(this);
}

CCmdEdit::~CCmdEdit()
{
	if(m_pConsumer)
		delete m_pConsumer;
}

void CCmdEdit::Append(LPCTSTR szText)
{
	CString strOut;
	
	strOut = _T("\r\n");
	strOut += szText;
	SetSel(-1, -1);
	ReplaceSel(strOut);
}

void CCmdEdit::AppendRaw(LPCTSTR szText)
{
	SetSel(-1, -1);
	ReplaceSel(szText);
}

CString CCmdEdit::AppendSelection()
{
	CString sBuffer;
	GetWindowText(sBuffer);
	long nStartChar, nEndChar;
	GetSel(nStartChar, nEndChar) ;
	sBuffer=sBuffer.Mid(nStartChar, nEndChar-nStartChar+1);
	SetSel(GetWindowTextLength(), -1);
	Append(sBuffer);
	::SendMessage(m_editCtrl.m_hWnd,WM_CHAR, VK_RETURN, 0);
	return sBuffer;

}
void CCmdEdit::ProcessCommand(CString strCmd)
{
	if(m_Spawn.IsExecuting())
	{
		strCmd += _T("\n");
		m_Spawn.SendInput(strCmd);
	}
	else
	{	
		try
		{
			m_Spawn.Execute(strCmd, m_pConsumer);
		}
		catch(...)
		{
		}
		Append(_T(""));
	}
}

/////////////////////////////////////////////////////////////////////////////
// CCmdEdit message handlers
LRESULT CCmdEdit::OnChar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled=false;
	switch (wParam)
	{
	case VK_RETURN:
		{
			//process command.
			int iLine, cb;
			TCHAR *pch;

			pch = m_strCmd.GetBuffer(_MAX_PATH);
			iLine = LineFromChar(-1);
			cb = GetLine(iLine, pch, _MAX_PATH);
			pch[cb] = _T('\0');
			m_strCmd.ReleaseBuffer();
			if(m_strCmd.GetLength())
			{
				ProcessCommand(m_strCmd);
			}
			else
			{
					Append(_T("\r\n"));
			}
			bHandled=true;
			return 0;

		}
	}
	return 1;
}

LRESULT CCmdEdit::OnGetDlgCode(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// TODO: Add your message handler code here and/or call default
	return DLGC_WANTALLKEYS | DLGC_HASSETSEL;
}



