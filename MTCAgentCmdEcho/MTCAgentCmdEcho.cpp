//
// MTCAgentCmdEcho.cpp : Defines the entry point for the console application.
//

// This software was developed by U.S. Government employees as part of
// their official duties and is not subject to copyright. No warranty implied 
// or intended.


#include "stdafx.h"
#include "MTCAgentCmdEcho.h"

#include "Shellapi.h"
#include <vector>
#include <string>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>

#include "sys/stat.h"
#include "string.h"
#include "fcntl.h"

#include "agent.hpp"
#include "config.hpp"
//#include "dlib/config_reader.h"
//#include <dlib/logger.h>


#include "NIST/StdStringFcn.h"

// Dont put the pragma lib before stdafx.h or you're screwed
#pragma comment( lib, "msxml2.lib" )
//#pragma comment(lib, "agent.lib")
#ifdef _DEBUG
#pragma message( "DEBUG WIN32 libxml2d.lib" )
#pragma comment(lib, "libxml2d.lib")
#else
#pragma message( "RELEASE WIN32  libxml2.lib" )
#pragma comment(lib, "libxml2.lib")
#endif


using namespace std;
using namespace dlib;


//static logger sLogger("main");
//static   const log_level LENTRY(400,"ENTRY");

static const char INI_FILENAME[] = "agent.cfg";
static const char LOG_FILENAME[] = "errors.log";

int AgentConfigurationEx::thread(int aArgc, const char *aArgv[])
{
	GLogger << INFO  << "MTConnect Agent Service Started " << nowtimestamp() << "\n";

#ifdef OBSERVER
	// Test out observer functionality
	Device *dev = getDeviceByName(devicename);
	DataItem *di = dev->getDeviceDataItem("Xabs");
	di->addObserver(new  BusyObserver("Xabs", di));
#endif
	try{
		long _sleep;
		char result[ MAX_PATH ];
		std::string path( result, GetModuleFileName( NULL, result, MAX_PATH ) );
		std::string cfgfile = path.substr(0,path.find_last_of(".")) + ".ini";
		if( GetFileAttributesA(cfgfile.c_str())!= INVALID_FILE_ATTRIBUTES)
		{
			config.load( cfgfile );
			_devices = config.GetTokens("CONFIG.Devices", ",");
			ipaddrs = config.GetTokens("CONFIG.CmdIp", ",");
			_xmldevices = config.GetTokens("CONFIG.XmlDevices", ",");
			_sleep=config.GetSymbolValue("CONFIG.Sleep","4000").toNumber<int>();
			_devicexmlpath =  config.GetSymbolValue("CONFIG.DevicesFolder", ::ExeDirectory()).c_str();
			_devicefile =  config.GetSymbolValue("CONFIG.DevicesFile", "Devices.xml").c_str();
			_cfgfile =  config.GetSymbolValue("CONFIG.CfgFile","Agent.cfg").c_str();
			_httpPort =  config.GetSymbolValue("CONFIG.HttpPort","81").toNumber<int>();
			_agentcfg.SetDevicesXmlFolder(_devicexmlpath);
			_agentcfg.SetHttpPort(_httpPort);
			_agentcfg.SetXmlFile(_devicefile);
			_agentcfg.SetCfgFile(_cfgfile);
			_agentcfg.SetDestinationFolder(::ExeDirectory());
			SetCurrentDirectory(::ExeDirectory().c_str()); // fixes Agent file lookup issue
		}
		for(int i=0; i< ipaddrs.size(); i++)
		{
			_agentcfg.AddDevice(_devices[i],  // M1, M2
				_xmldevices[i], // lookup name in devices.xml folder
				ipaddrs[i], 
				"0");			//writing to agent will be done using thread pointer not SHDR

			CCmdHandler *  _cmdHandler = new CCmdHandler(this);
			_cmdHandler->_nSleep = _sleep; // amount of sleeping per cycle
			_cmdHandlers.push_back(_cmdHandler);
			_cmdHandler->Configure( config,_devices[i], _xmldevices[i], ipaddrs[i],_devicexmlpath);
			_group.create_thread(boost::bind(&CCmdHandler::Cycle, _cmdHandler));
		}

		_agentcfg.WriteCfgFile(_cfgfile, _devicefile, ::ExeDirectory());

		//_agentcfg.Start();  // can just use the regular start of below, need to cofigure main?
		char *argv[5] = {
			"agent.exe",
			"run",
			"" ,"",""
		};
		file =  ::ExeDirectory() + _cfgfile ; // change if not Agent.cfg
		argv[2]= new char[file.size() + 1]; 
		strcpy(argv[2], file.c_str()); 
		MTConnectService::main( 2,(const char **) argv);

	}
	catch(...) {}

	return 0;
}

void AgentConfigurationEx::initialize(int aArgc, const char *aArgv[])
{
  MTConnectService::initialize(aArgc, aArgv);
  mConfigFile =file;
  /** 
  Problems:
  1)Agent::Agent
     std::set<std::string> uuids;
    for (device = mDevices.begin(); device != mDevices.end(); ++device) 
    {
      if (uuids.count((*device)->getUuid()) > 0)
          throw runtime_error("Duplicate UUID: " + (*device)->getUuid());
      
      uuids.insert((*device)->getUuid());
    }

	2)Agent::Agent (last item)
  sLogger << LFATAL << "Duplicate DataItem id " << d->getId() <<
  " for device: " << (*device)->getName() << " and data item name: " <<
  d->getName();
  exit(1);

  */
  try
  {
    configureLogger();
    ifstream file(mConfigFile.c_str());
    loadConfig(file);
  }
  catch(std::exception e)
  {
	  GLogger << FATAL << "Agent failed to load: " << e.what();

  }
  catch(...)
  {
	  GLogger << FATAL << "Agent failed to load: " << std::endl;

  }


}
// Start the server. This blocks until the server stops.
void AgentConfigurationEx::start()
{
	cond.notify_all();  
	AgentConfiguration::start();
}
void AgentConfigurationEx::stop()
{
	for(int i=0; i< _cmdHandlers.size(); i++)
		_cmdHandlers[i]->Stop();

	_group.join_all();
	AgentConfiguration::stop();
}


int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}


#pragma comment(linker, "/SUBSYSTEM:WINDOWS")
#pragma warning(disable: 4247) //warning C4297: 'WinMain' : function assumed not to throw an exception but does

int APIENTRY WinMain(HINSTANCE hInstance,
					 HINSTANCE hPrevInstance,
					 LPTSTR    lpCmdLine,
					 int       nCmdShow)
{

	AgentConfigurationEx config;

	//READY, ACTIVE, INTERRUPTED, or STOPPED 
	// Version 0.9 EXECUTION IDLE, EXECUTING, or PAUSED
	//Adapter::keymapping["execution.READY"]="IDLE";
	//Adapter::keymapping["execution.ACTIVE"]="EXECUTING";
	//Adapter::keymapping["execution.INTERRUPTED"]="PAUSED";
	//Adapter::keymapping["execution.STOPPED"]="PAUSED";
	//Adapter::keymapping["mode"]="controllermode";
	//Adapter::keymapping["Fovr"]="path_feedrateovr";
	//Adapter::keymapping["Fact"]="path_feedratefrt";

	//_CrtSetBreakAlloc(310); // if no  break, then must be "static" allocated beforehand
	try 
	{
		//config.configfile() = ExeDirectory() + INI_FILENAME;

		//config.configureLogger();
		GLogger << INFO  << "MTConnect Agent Service Started " << nowtimestamp() << "\n";
		if(FAILED(::CoInitialize(NULL)))
			throw  std::exception("CoInitialize failed\n");

		HRESULT hr = ::CoInitializeSecurity( NULL, //Points to security descriptor 
			-1, //Count of entries in asAuthSvc 
			NULL, //Array of names to register 
			NULL, //Reserved for future use 
			RPC_C_AUTHN_LEVEL_NONE, //The default authentication //level for proxies 
			RPC_C_IMP_LEVEL_IDENTIFY, //The default impersonation //level for proxies 
			NULL, //Reserved; must be set to  NULL
			EOAC_NONE, //Additional client or //server-side capabilities 
			NULL //Reserved for future use 
			);  

		if(FAILED(hr))
			throw std::exception("CoInitializeSecurity failed\n");
		SetCurrentDirectory(ExeDirectory().c_str());

		//std::cout.rdbuf(&DebugLogger);
		//std::cerr.rdbuf(&DebugLogger);
		//DebugBreak();

		config.thread( __argc,(const char **) __argv );

		GLogger << FATAL  << "MTConnect Agent Service Aborted " << nowtimestamp() <<  "\n";
		//::ExitProcess(0);
		//SetErrorMode(GetErrorMode () | SEM_NOGPFAULTERRORBOX);  // vista
		_set_abort_behavior(0, _WRITE_ABORT_MSG | _CALL_REPORTFAULT);
		//abort();
		::TerminateProcess(::GetCurrentProcess(),  -1); // Zero is the exit code
		throw std::exception("Done");

		// Main message loop:
		MSG msg;
		while (GetMessage(&msg, NULL, 0, 0))
		{
			if (!TranslateAccelerator(msg.hwnd, NULL, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	}
	catch(std::exception e)
	{
		OutputDebugString(e.what());
		GLogger << FATAL  << e.what() << "\n";
	}
	catch(...)
	{
		OutputDebugString("Service terminated abnormally in main\n");
		GLogger << FATAL  << "Service terminated abnormally in main\n";
	}
	GLogger << INFO  << "MTConnect Agent Service Stopped" << nowtimestamp() << "\n";
	return -1;
}