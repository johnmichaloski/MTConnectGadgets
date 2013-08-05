// ShdrFileEchoView.h : interface of the CShdrFileEchoView class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include "ComMTCShdrBackEnd.h"
#include <iostream>
#include <fstream>
#include "ATLComTime.h"
#include "MTConnectDeviceParser.h"
#include "Logger.h"

class CShdrFileEchoView : public CDialogImpl<CShdrFileEchoView>,
	 public CDialogResize<CShdrFileEchoView>
{
public:
	enum { IDD = IDD_SHDRFILEECHO_FORM };
	

	CShdrFileEchoView();

	BOOL PreTranslateMessage(MSG* pMsg);

	BEGIN_DLGRESIZE_MAP(CShdrFileEchoView)
		DLGRESIZE_CONTROL(IDC_ECHOEDIT, DLSZ_SIZE_X|DLSZ_SIZE_Y)
	END_DLGRESIZE_MAP()

	BEGIN_MSG_MAP(CShdrFileEchoView)
		MESSAGE_HANDLER(WM_TIMER, OnTimer)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		 CHAIN_MSG_MAP(CDialogResize<CShdrFileEchoView>)
	END_MSG_MAP()

	int GetNextTokens();
	void OutputTokens();
	void EchoShdr(const TCHAR * msg);
	void Open() { in.open(_filename.c_str());  }
	void Start();
	void Close(void);

	std::string & Filename() { return _filename; }

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)
	LRESULT OnTimer(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);


	CComPtr<CoComMTCShdrBackEnd> _backend;
	MTConnectDeviceParser _deviceparser;
	DeviceModel _devicemodel;
	std::ifstream in;
	std::stringstream strbuffer; 
	std::string _buffer;
	std::string _filename;
	DataDictionary _dict;
	std::vector<std::string> tokens;
	COleDateTime lasttime;
	COleDateTime intime;
	COleDateTimeSpan diff;
	bool _bRepeat;
	double _dOverride;

	MapValues  localvalues;



	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
};
