//
// MtConnectDboard.cpp : main source file for MtConnectDboard.exe
//
// DISCLAIMER:
// This software was developed by U.S. Government employees as part of
// their official duties and is not subject to copyright. No warranty implied 
// or intended.

#include "stdafx.h"

#include "resource.h"
#include "MtConnectDboard.h"
#include <boost/timer.hpp>
#include "service.hpp"
#include <functional>
#include <numeric>
#include <algorithm>
#include "Logger.h"
#include <boost/config/user.hpp>
// Tests
#include "DataArchiver.h"
#include "DBLogger.h"
#include "AlarmHandler.h"
#include "OdbcArchiver.h"

CAppModule _Module;
CComPtr<IGlobalInterfaceTable> pGIT;
HANDLE CMtConnectDboard::hBrowserMutex; 

static void trans_func( unsigned int u, EXCEPTION_POINTERS* pExp )
{
	std::string errmsg = StdStringFormat("CMtConnectDboard trans_func - Code = 0x%x\n",  
		pExp->ExceptionRecord->ExceptionCode) ;

	GLogger << FATAL << "CMtConnectDboard Exception Raised\n" << errmsg << std::endl;
	throw std::exception(errmsg.c_str());
}

//extern void test();

extern void StatTest();
	////////////////////////////////////////
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpstrCmdLine, int nCmdShow)
{
	AtlTrace("_tWinMain Enter");
	_set_se_translator( trans_func );  // correct thread?
	HRESULT hRes = ::CoInitialize(NULL);
	hRes = _Module.Init(NULL, hInstance);
	CoCreateInstance(CLSID_StdGlobalInterfaceTable,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IGlobalInterfaceTable,
		(void **)&pGIT);

	/*StatTest();*/

#if 0
	CAlarmHandler alarm;
	std::vector<std::string> faults = TrimmedTokenize("HydraulicLevel,HydraulicPressure,HydraulicTemp,CoolantLow,LogicProgram,Cloadc,Xloadc,Yloadc,Zloadc,condition", ",");
	alarm.Configure(faults, 
		::ExeDirectory(),
		"M001"
		);
	OutputDebugString(alarm.MTBF().c_str());
	OutputDebugString(alarm.MTTR().c_str());
#endif
	GLogger.Open(0);
	CMtConnectDboard myservice;
	myservice.setName("MtConnectDboard");
	myservice.main(__argc, (const char **) __argv);
	AtlTrace("_tWinMain Exit1");
	_Module.Term();
	AtlTrace("_tWinMain Exit2");
	::CoUninitialize();
	AtlTrace("_tWinMain Exit3");

}

CMtConnectDboard::CMtConnectDboard()// : dlgMain(this)
{
	hBrowserMutex = CreateMutex( 
		NULL,                       // default security attributes
		FALSE,                      // initially not owned
		NULL);  
	if (hBrowserMutex == NULL) 
		AtlTrace("CMtConnectDboard() CreateMutex error: %d\n", GetLastError());
 
	m_ThreadEndEvent=CreateEvent(NULL,		// default security attributes
		FALSE,								// manual-reset event
		TRUE,								// initial state is nonsignaled
		"CMtConnectDboard Done");
}
CMtConnectDboard::~CMtConnectDboard()
{
	//delete _snapshot;
	CloseHandle(hBrowserMutex);
}

void CMtConnectDboard::logoff()
{
	AtlTrace("CMtConnectDboard::logoff");
	for(int i=0; i< _snapshots.size(); i++)
		_snapshots[i]->Logoff();
	KillProgram("MtConnectDboardGui.exe");
}
void CMtConnectDboard::logon()
{
	AtlTrace("CMtConnectDboard::logon");
	KillProgram("MtConnectDboardGui.exe");
	for(int i=0; i< _snapshots.size(); i++)
		_snapshots[i]->Logon();

}
void CMtConnectDboard::initialize(int aArgc, const char *aArgv[])
{
	GLogger << FATAL << "CEchoService::initialize(int aArgc, const char *aArgv[])" << std::endl; 
	char result[ MAX_PATH ];
	std::string path( result, GetModuleFileName( NULL, result, MAX_PATH ) );
	std::string cfgfile = path.substr(0,path.find_last_of(".")) + ".ini";
	if( GetFileAttributesA(cfgfile.c_str())!= INVALID_FILE_ATTRIBUTES)
	{
		config.load( cfgfile );

		// Service name
		std::string servicename =  config.GetSymbolValue("CONFIG.ServiceName", L"MtConnectDboard").c_str();
		setName(servicename.c_str());
			
		// Globals
		GLogger.DebugLevel()=  config.GetSymbolValue("CONFIG.Debug", L"0").toNumber<int>();
		GLogger.Timestamping()= (bool) config.GetSymbolValue("CONFIG.Timestamp", L"0").toNumber<int>();
		
		MTConnectStreamsParser::_TagRenames =  config.getmap("ALIASES");
		MTConnectStreamsParser::_valuerenames =  config.getmap("VALUEREMAPPING");
		MTConnectStreamsParser::_saveddata = config.GetTokens("CONFIG.Data", ",");

		std::string ipaddr =  config.GetSymbolValue("DEVICES.IP", L"127.0.0.1").c_str();
		ipaddrs=TrimmedTokenize(ipaddr,",");
		std::string sMachine =  config.GetSymbolValue("DEVICES.Machine", L"DMG2796").c_str();
		sMachines=TrimmedTokenize(sMachine,",");
		if(ipaddrs.size() != sMachines.size())
		{
			GLogger << FATAL << "CEchoService::initialize # ip addresses != # machines" << std::endl; 

		}
	}
	else
	{
		GLogger << FATAL <<"Could not find ini configuration file" << cfgfile << std::endl; 
	}

	MTConnectService::initialize(aArgc, aArgv);
}
void CMtConnectDboard::start()
{
	HRESULT hRes = ::CoInitialize(NULL);
	AtlTrace("CEchoService::start())");
	serviceThread(); // not really thread anymore, never returns
}
void CMtConnectDboard::stop()
{
	GLogger << FATAL <<"CEchoService::stop())" << std::endl; 
	//CServiceEndThread * enditThread = new CServiceEndThread(this, dlgThread);
	//enditThread->Resume();
	AtlTrace("CMtConnectDboard::stop() thread done");
	for(int i=0; i< _snapshots.size(); i++)
		_snapshots[i]->Shutdown();

	::WaitForSingleObject(m_ThreadEndEvent, 5000 );
	KillProgram("MtConnectDboardGui.exe");
}
void CMtConnectDboard::serviceThread()
{
	GLogger << FATAL << "CEchoService::serviceThread()" << std::endl; 
	_set_se_translator( trans_func );  // correct thread?

	try {
		::Sleep(1000*5);
		for(int i=0; i< ipaddrs.size(); i++)
		{
			CHtmlTableSnapshots *  snapshot = new CHtmlTableSnapshots();
			std::string machine;
			if( i>= sMachines.size())
				machine="Machine name missing - please fix";
			else machine=sMachines[i];

			_snapshots.push_back(snapshot);
			snapshot->Configure( config,
				machine, // machine name
				ipaddrs[i],
				""); // ip address of agent
			group.create_thread(boost::bind(&CHtmlTableSnapshots::Cycle, snapshot));
			::Sleep(1000);
		}
		group.join_all();

	}
	catch(std::exception e)
	{
		AtlTrace("%s%s", "CEchoService::serviceThread() exception " , e.what());
	}
	catch(...)
	{
		AtlTrace("CEchoService::serviceThread() exception ");
	}
//	parser.Release();
	if(m_ThreadEndEvent != NULL)
		SetEvent(m_ThreadEndEvent);	
	//::CoUninitialize();
	AtlTrace("CEchoService::serviceThread() Exit");
}