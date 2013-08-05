//
// CmdEdit.h : header file
//

#pragma once
#include "spawn.h"

class CCmdEdit;	
class CSpawnConsumer1;

/////////////////////////////////////////////////////////////////////////////
// CCmdEdit window
 
class CCmdEdit : public CWindowImpl<CCmdEdit, CRichEditCtrl>,		
	public CEditCommands<CCmdEdit>

{
public:
	//DECLARE_WND_SUPERCLASS(NULL, CEdit::GetWndClassName())
	DECLARE_WND_SUPERCLASS(NULL, CRichEditCtrl::GetWndClassName())

	BOOL PreTranslateMessage(MSG* pMsg)
	{
		pMsg;
		return FALSE;
	}

	BEGIN_MSG_MAP(CCmdEdit)
		MESSAGE_HANDLER(WM_CHAR, OnChar)
		MESSAGE_HANDLER(WM_GETDLGCODE, OnGetDlgCode)
		CHAIN_MSG_MAP_ALT(CEditCommands<CCmdEdit>, 1)
	END_MSG_MAP()
	LRESULT OnChar(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnGetDlgCode(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)
// Construction
public:
	CRichEditCtrl m_editCtrl;
	CCmdEdit();
	virtual ~CCmdEdit();
	
	void	Append(LPCTSTR szText);
	void	AppendRaw(LPCTSTR szText);
	CString	AppendSelection();

	
	CSpawn					m_Spawn;
	void ProcessCommand(CString strCmd);

	
	// Generated message map functions
protected:		
	CString					m_strCmd;
	CSpawnConsumer1*		m_pConsumer;
};


class CSpawnConsumer1 : public CSpawnConsumer
{
public:
	CSpawnConsumer1(CCmdEdit* pEdit) {m_pEdit = pEdit;}
	void Consume(TCHAR* p, DWORD)
	{
		m_pEdit->AppendRaw(p);
	}
	
private:
	CCmdEdit* m_pEdit;
};

