// CMSDCommandCell.cpp : main source file for CMSDCommandCell.exe
//
// C:\Program Files\NIST\proj\MTConnect\Nist\MTConnectGadgets\CMSDCommandCell\CMSDCommandCell\CMSDCommandCell.cpp

#include "stdafx.h"
#include "resource.h"
#include "CMSDCommandCellView.h"
#include "MainFrm.h"
#include "MTCAgentCmd.h"
#include "logger.h"
///#pragma comment( lib, "msxml2.lib" )

#pragma comment(lib, "Ws2_32.lib")


#if defined(WIN64) && defined( _DEBUG) 
#pragma message( "DEBUG x64" )
#pragma comment(lib, "libxml2_64d.lib")
#pragma comment(lib, "libboost_thread-vc100-mt-sgd-1_44.lib")
#elif !defined( _DEBUG) && defined(WIN64)
#pragma message( "RELEASE x64" )
#pragma comment(lib, "libxml2_64.lib")
#pragma comment(lib, "libboost_thread-vc100-mt-s-1_44.lib")
#elif defined(_DEBUG) && defined(WIN32)
#pragma message( "DEBUG x32" )
#pragma comment(lib, "libxml2d.lib")
#pragma comment(lib, "libboost_thread-vc100-mt-sgd-1_44.lib")
#elif !defined( _DEBUG) && defined(WIN32)
#pragma message( "RELEASE x32" )
#pragma comment(lib, "libboost_thread-vc100-mt-s-1_44.lib")
#pragma comment(lib, "libxml2.lib")
#endif

CAppModule _Module;
CMainFrame * _wndMain;
CLogger FurLogger;

int Run(LPTSTR /*lpstrCmdLine*/ = NULL, int nCmdShow = SW_SHOWDEFAULT)
{
	CMessageLoop theLoop;
	_Module.AddMessageLoop(&theLoop);

	CMainFrame wndMain;
	_wndMain=&wndMain;

	FurLogger.Open(::ExeDirectory() + "LINE1_PS_CAST1_FUR1.txt");
	FurLogger.DebugString()=true;
	FurLogger.Timestamping()=true;
	FurLogger.DebugLevel()=5;

	GLogger.DebugString()=false;

	// job -> part -> processplan -> steps(processses) -> cells(resources) + misc.

	//sd::string test1 =  cmsd.GenerateSchema("Factory") ;
	//WriteFile(::ExeDirectory() + "cmsd-create.sql",test1);
	//test1 = cmsd.GenerateTableData("Factory") ;
	//WriteFile(::ExeDirectory() + "cmsd-insert.sql",test1);

	//cmsd.OpenSqlDatabase("CMSD");
	//cmsd.OpenSqlDatabase("ConsolidatedData");
	//cmsd.LoadCMSDFromSql();

	GLogger.DebugString()=true;
	GLogger.Timestamping()=true;
	//GLogger.Open(::ExeDirectory() + "debug.txt");

	if(wndMain.CreateEx() == NULL)
	{
		ATLTRACE(_T("Main window creation failed!\n"));
		return 0;
	}

	wndMain.ShowWindow(nCmdShow);

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

	AtlInitCommonControls(ICC_BAR_CLASSES);	// add flags to support other controls

	hRes = _Module.Init(NULL, hInstance);
	ATLASSERT(SUCCEEDED(hRes));

	int nRet = Run(lpstrCmdLine, nCmdShow);

	_Module.Term();
	::CoUninitialize();

	return nRet;
}
