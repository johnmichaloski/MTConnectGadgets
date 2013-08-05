// CMSDBuilder.cpp : main source file for CMSDBuilder.exe
//

#include "stdafx.h"

#include "resource.h"

#include "CMSDBuilderView.h"
#include "aboutdlg.h"
#include "MainFrm.h"
#include "CMSD/CMSD.h"
#include <string>
#include "StdStringFcn.h"
#include <comdef.h>
#include "ComArenaHook.h"
#include "MTConnectStreamsParser.h"

using namespace std;
using namespace CMSD;

CAppModule _Module;

int Run(LPTSTR lpstrCmdLine = NULL, int nCmdShow = SW_SHOWDEFAULT)
{
	CMessageLoop theLoop;
	_Module.AddMessageLoop(&theLoop);

	//CMTConnectStreamsParser parser;
	//parser.AddMTConnectDevice("127.0.0.1");
	////parser.AddMTConnectDevice("127.0.0.1/M1");
	//parser.Start();
	//Sleep(10000);
	//parser.Stop();
	//parser.Join(2000);
	CMainFrame wndMain;

	if(wndMain.CreateEx() == NULL)
	{
		ATLTRACE(_T("Main window creation failed!\n"));
		return 0;
	}

	wndMain.ShowWindow(nCmdShow);

	MTConnections.Start();

	int nRet = theLoop.Run();

	_Module.RemoveMessageLoop();
	return nRet;
}

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpstrCmdLine, int nCmdShow)
{
	HRESULT hRes = ::CoInitialize(NULL);
// If you are running on NT 4.0 or higher you can use the following call instead to 
// make the EXE free threaded. This means that calls come in on a random RPC thread.
//	HRESULT hRes = ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
	ATLASSERT(SUCCEEDED(hRes));

	// this resolves ATL window thunking problem when Microsoft Layer for Unicode (MSLU) is used
	::DefWindowProc(NULL, 0, 0, 0L);

	AtlInitCommonControls(ICC_COOL_CLASSES | ICC_BAR_CLASSES);	// add flags to support other controls

	hRes = _Module.Init(NULL, hInstance);
	ATLASSERT(SUCCEEDED(hRes));

	AtlAxWinInit();

	int nRet = Run(lpstrCmdLine, nCmdShow);

	_Module.Term();
	::CoUninitialize();

	return nRet;
}
