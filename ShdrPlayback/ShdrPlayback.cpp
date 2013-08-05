//
// ShdrFileEcho.cpp : main source file for ShdrFileEcho.exe
//

// This software was developed by U.S. Government employees as part of
// their official duties and is not subject to copyright. No warranty implied 
// or intended.

#include "stdafx.h"

#include "resource.h"

#include "ShdrFileEchoView.h"
#include "MainFrm.h"
#include "ShdrEcho.h"
#include "StdStringFcn.h"
#include "Config.h"
#include <stdlib.h>
#include <boost/program_options.hpp>
using namespace  boost::program_options;
CAppModule _Module;

int Run(LPTSTR lpstrCmdLine = NULL, int nCmdShow = SW_SHOWDEFAULT)
{
	CMessageLoop theLoop;
	_Module.AddMessageLoop(&theLoop);
	// Check to see if cfg file exists
	char result[ MAX_PATH ];
	std::string path( result, GetModuleFileName( NULL, result, MAX_PATH ) );
	std::string cfgfile = path.substr(0,path.find_last_of(".")) + ".ini";
	Distribution mtbfstat,mttrstat;
	mtbfstat.SetParameters(_T("normal"), 5, 0.1);
	mttrstat.SetParameters(_T("normal"), 6, 0.1);
	CShdrEchoCollection shdrs;

	std::string shdrfilename=::ExeDirectory() + "M25751-12-03-09.txt";
	std::string devicefilename=::ExeDirectory() + "Devices.xml";
	double dOverride = 100;
	int ipport=7878;
	 
	options_description desc("Allowed options");
	desc.add_options()
		("-p", value<int>(), "IP Port")
		("-d", value<std::string>(&devicefilename), "Devices xml file")
		("-s", value<std::string>(&shdrfilename), "Shdr Script file")
		;
	if(__argc > 1)
	{
		try {
			AtlTrace(StdStringFormat("ShdrPlayback %s\n", lpstrCmdLine).c_str());
			variables_map vm;
			std::vector<std::string> args = split_winmain(lpstrCmdLine);
			store(command_line_parser(args).options(desc).run(), vm);
			if (vm.count("-p")) { ipport= vm["-p"].as<int>();}
			if (vm.count("-d")) { devicefilename= vm["-d"].as<std::string>();}
			if (vm.count("-s")) { shdrfilename= vm["-s"].as<std::string>();}

		}
		catch(std::exception e)
		{
			AtlTrace(e.what());
		}
		AtlTrace(StdStringFormat("ShdrPlayback Add Echo %s %s %d %d \n", 
			devicefilename.c_str(), shdrfilename.c_str(), ipport, dOverride).c_str());
		CShdrEchoInstance * shdr = shdrs.AddShdrEcho(devicefilename, shdrfilename, ipport, dOverride);
		shdr->SetFault(mtbfstat,mttrstat);
	}

	else if( GetFileAttributesA(cfgfile.c_str())!= INVALID_FILE_ATTRIBUTES)
	{
		crp::Config config;
		config.load( cfgfile );
		std::vector<std::string>sections =  config.GetSections() ;
		for(int i=0; i< sections.size(); i++)
		{
			devicefilename =  config.GetSymbolValue(sections[i]+".devicesfile", L"").c_str();
			shdrfilename =  config.GetSymbolValue(sections[i]+".shdrfile", L"").c_str();
			ipport =  config.GetSymbolValue(sections[i]+".ipport", L"7878").toNumber<int>();
			dOverride =  config.GetSymbolValue(sections[i]+".override", L"100").toNumber<double>();
			std::string sMtbf =  config.GetSymbolValue(sections[i]+".MTBF", L"").c_str();
			std::string sMttr =  config.GetSymbolValue(sections[i]+".MTTR", L"").c_str();
			if(!sMtbf.empty())
			{
				std::vector<std::string> tokens = TrimmedTokenize(sMtbf,",");
				if(tokens.size() > 1)
					mtbfstat.SetParameters(_T("normal"), 
					ConvertString<double>(tokens[1],0),
					(tokens.size() > 2)? ConvertString<double>(tokens[2],0): 0,
					(tokens.size() > 3)? ConvertString<double>(tokens[3],0): 0,
					(tokens.size() > 4)? ConvertString<double>(tokens[4],0): 0
					);
			}
			if(!sMttr.empty())
			{
				std::vector<std::string> tokens = TrimmedTokenize(sMttr,",");
				if(tokens.size() > 1)
					mttrstat.SetParameters(_T("normal"), 
					ConvertString<double>(tokens[1],0),
					(tokens.size() > 2)? ConvertString<double>(tokens[2],0): 0,
					(tokens.size() > 3)? ConvertString<double>(tokens[3],0): 0,
					(tokens.size() > 4)? ConvertString<double>(tokens[4],0): 0
					);
			}
			CShdrEchoInstance * shdr =  shdrs.AddShdrEcho(devicefilename, shdrfilename, ipport, dOverride);
			shdr->SetFault(mtbfstat,mttrstat);
		}
	}

	if(shdrs.size() < 1)
		return 0;
	//RedirectIOToConsole();
	shdrs.StartAll();
	shdrs.StopAll();
	return 0;
	CMainFrame wndMain;

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
