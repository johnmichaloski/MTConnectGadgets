/*
* Copyright (c) 2008, AMT – The Association For Manufacturing Technology (“AMT”)
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*     * Redistributions of source code must retain the above copyright
*       notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in the
*       documentation and/or other materials provided with the distribution.
*     * Neither the name of the AMT nor the
*       names of its contributors may be used to endorse or promote products
*       derived from this software without specific prior written permission.
*
* DISCLAIMER OF WARRANTY. ALL MTCONNECT MATERIALS AND SPECIFICATIONS PROVIDED
* BY AMT, MTCONNECT OR ANY PARTICIPANT TO YOU OR ANY PARTY ARE PROVIDED "AS IS"
* AND WITHOUT ANY WARRANTY OF ANY KIND. AMT, MTCONNECT, AND EACH OF THEIR
* RESPECTIVE MEMBERS, OFFICERS, DIRECTORS, AFFILIATES, SPONSORS, AND AGENTS
* (COLLECTIVELY, THE "AMT PARTIES") AND PARTICIPANTS MAKE NO REPRESENTATION OR
* WARRANTY OF ANY KIND WHATSOEVER RELATING TO THESE MATERIALS, INCLUDING, WITHOUT
* LIMITATION, ANY EXPRESS OR IMPLIED WARRANTY OF NONINFRINGEMENT,
* MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. 

* LIMITATION OF LIABILITY. IN NO EVENT SHALL AMT, MTCONNECT, ANY OTHER AMT
* PARTY, OR ANY PARTICIPANT BE LIABLE FOR THE COST OF PROCURING SUBSTITUTE GOODS
* OR SERVICES, LOST PROFITS, LOSS OF USE, LOSS OF DATA OR ANY INCIDENTAL,
* CONSEQUENTIAL, INDIRECT, SPECIAL OR PUNITIVE DAMAGES OR OTHER DIRECT DAMAGES,
* WHETHER UNDER CONTRACT, TORT, WARRANTY OR OTHERWISE, ARISING IN ANY WAY OUT OF
* THIS AGREEMENT, USE OR INABILITY TO USE MTCONNECT MATERIALS, WHETHER OR NOT
* SUCH PARTY HAD ADVANCE NOTICE OF THE POSSIBILITY OF SUCH DAMAGES.
*/
#include "stdafx.h"
#include "Shellapi.h"

#include "sys/stat.h"
#include "string.h"
#include "fcntl.h"

#include "agent.hpp"
#include "config.hpp"

#include "dlib/config_reader.h"
#include <dlib/logger.h>
#include "dlib/timeout/timeout_kernel_1.h"
#include <ATLComTime.h>

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif


using namespace std;
using namespace dlib;

//#include "MachineAdapter.h"
#include "NIST/StdStringFcn.h"

static logger sLogger("main");
static   const log_level LENTRY(400,"ENTRY");

static const char INI_FILENAME[] = "agent.cfg";
static const char LOG_FILENAME[] = "debug.log";


extern SERVICE_STATUS          gSvcStatus; 
extern VOID ReportSvcStatus( DWORD dwCurrentState, //    The current state (see SERVICE_STATUS)
					 DWORD dwWin32ExitCode, //   The system error code
					 DWORD dwWaitHint); //    Estimated time for pending operation, 

static void trans_func( unsigned int u, EXCEPTION_POINTERS* pExp )
{
	OutputDebugString( StdStringFormat("AgentConfigurationEx::In trans_func - Code = 0x%x\n",  pExp->ExceptionRecord->ExceptionCode).c_str() );
#ifdef DEBUG
	DebugBreak();
#endif
	throw std::exception();
}

class AgentConfigurationEx : public AgentConfiguration
{
public:
	AgentConfigurationEx() : 
	  _bResetAtMidnight(false)	  
	  {
		  _bRunning=false;
#ifdef OPC
		  _bOPCEnabled=false; 
#endif
	  }
	  virtual void start()
	   {
		  sLogger << LENTRY  << "MTConnect Agent Service Started " << nowtimestamp() << "\n";
		  OutputDebugString(StdStringFormat( "MTConnect Agent Service Start %s\n" , COleDateTime::GetCurrentTime().Format() ).c_str());
		  try{
			  struct stat buf;
			  std::string path = ExeDirectory() + INI_FILENAME;
			  if (stat(path.c_str(), &buf) != 0) 
				  throw std::exception(("Ini file doesn't exist " + path).c_str());

			  reader.load_from(std::ifstream ((ExeDirectory() + INI_FILENAME).c_str()));
			  _bResetAtMidnight = ConvertString<bool>(reader.block("OPCSERVER")["ResetAtMidnight"], false);
			  if(_bResetAtMidnight)
				  OutputDebugString("Agent will Reset At Midnight\n");

			  _bRunning=true; 
			  _hThread.Attach((HANDLE) _beginthreadex( NULL, 0, &AgentConfigurationEx::ResetAtMidnightThread, this, 0, &_threadID ));

#ifdef OPC
			  if (reader.is_block_defined("OPCSERVER") && reader.block("OPCSERVER").is_key_defined("OPCEnabled"))
				  _bOPCEnabled= ConvertFromString<bool>(reader.block("OPCSERVER")["OPCEnabled"], false);
			  if(_bOPCEnabled)
				 StartOPCMachines();//StartOpc();
#endif
			  //Handles Win32 exceptions (C structured exceptions) as C++ typed exceptions
			  //_set_se_translator( trans_func ); 

			  // Start the server. This blocks until the server stops.
			  AgentConfiguration::start();

		  }
		  catch(std::exception e)
		  {
			  OutputDebugString(StdStringFormat("AgentConfigurationEx::start() failed - %s\n", e.what()).c_str());
			  throw e;
		  }
		  catch(...) {}

	  }
#ifdef OPC
	  static DWORD WINAPI StartOpcThread(void * pObj){ ((AgentConfigurationEx *) pObj)->StartOPCMachines(); return 0; }
	  virtual void StartOpc()
	  {
		  OutputDebugString(StdStringFormat( "MTConnect Agent Service Start OPC %s\n" , COleDateTime::GetCurrentTime().Format() ).c_str());
		  CHandle thread(::CreateThread(0, // default security
			  0, // default stack size
			  StartOpcThread,
			  this, // context
			  0, // no flags
			  0)); // ignore thread id	  
	  }

	  void StartOPCMachines()
	  {	  
		  try {
		      machines.clear();
			  if(_bOPCEnabled)
			  {
				  /////////////////////////////////////
				  /// BEGIN OPC Related Code
				  struct stat buf;
				  std::string path = ExeDirectory() + INI_FILENAME;
				  if (stat(path.c_str(), &buf) != 0) 
					  throw std::exception(("Ini file doesn't exist " + path).c_str());

				  std::vector<std::string> servers = Tokenize(reader.block("OPCSERVER")["ServerMachineName"], ",");
				  std::vector<std::string> devices = Tokenize(reader.block("OPCSERVER")["MTConnectDevice"], ",");
				  std::vector<std::string> tags = Tokenize(reader.block("OPCSERVER")["OpcTags"], ",");
				  if(servers.size() != devices.size() && servers.size() != tags.size())
					  throw std::exception("OPC Number of Server IPs does not match number of MTConnect devices or Section Tags" );

				  for(int i=0; i< servers.size(); i++)
				  {
					  CMachineAdapter * _opc= new CMachineAdapter((AgentConfiguration *) this, Trim(servers[i]), Trim(devices[i]), Trim(tags[i])); // for now load in device name
					  machines.push_back(_opc);
					  if(FAILED(_opc->ReadOPCSettings(path)))
						  throw std::exception("Error in reading OPCSettings - see log for details.\n" );
					  _opc->Start() ;
				  }

				  /// END OPC Related Startup  Code
				  /////////////////////////////////////
			  }
		  }
		  catch(std::exception e)
		  {
			  OutputDebugString(StdStringFormat("AgentConfigurationEx::StartOPCMachines() failed - %s\n", e.what()).c_str());
			  throw e;
		  }
		  catch(...) {}
	  }
	  void StopOPCMachines()
	  {
		  if(_bOPCEnabled)
		  {
			  // This appears sufficient
			  for(int i=0; i< machines.size(); i++)
				  machines[i]->Stop() ;
			  // Trouble...
			  for(int i=0; i< machines.size(); i++)
			  {
			  	machines[i]->Join(5000) ;
				OutputDebugString(StdStringFormat("CMachineAdapter(%s) Officially Exited:%s\n" , machines[i]->_device.c_str(), COleDateTime::GetCurrentTime().Format()).c_str());
			  }
			  
			  // BUG!!!!!!!! Known "Small" leak.
			  //for(int i=0; i< machines.size(); i++)
			  //	delete machines[i]
			  //machines.clear();
		  }
	  }
#endif
	  virtual void stop()
	  {
#ifdef THREADEDSTOP
		   CHandle thread(::CreateThread(0, // default security
                                  0, // default stack size
                                  StopThread,
                                  this, // context
                                  0, // no flags
                                  0)); // ignore thread id
#else
		  int nWaitTime = 5000;
#ifdef OPC
		nWaitTime += 5000 * machines.size();
#endif
		  ReportSvcStatus(SERVICE_STOP_PENDING, 0, 15000);
		  StopAll();
		  ReportSvcStatus(SERVICE_STOP, 0, 0);
#endif
	  }
	  static DWORD WINAPI StopThread(void * pObj)
	  {
		  ReportSvcStatus(SERVICE_STOP_PENDING, 0, 10000);
		  ((AgentConfigurationEx *) pObj)->StopAll();
		  ReportSvcStatus(SERVICE_STOP, 0, 0);
		  return 0;
	  }
	  void StopAll()
	  {
		  try {
			  // Check if invoked from SCM as opposed to midnite reset.
			  AgentConfiguration::stop();
			  if( _hThread!=NULL && _bRunning)
			  {
				  BOOL  bTerminate= TerminateThread(_hThread, 0);
			  }
			  OutputDebugString(StdStringFormat( "MTConnect Agent Service Stopping %s\n", COleDateTime::GetCurrentTime().Format() ).c_str());
#ifdef OPC
			  StopOPCMachines();
#endif
			  OutputDebugString(StdStringFormat( "MTConnect Agent Service Stopped %s\n", COleDateTime::GetCurrentTime().Format() ).c_str());
		  }
		  catch(...)
		  {
			  OutputDebugString(StdStringFormat( "MTConnect Agent Service Stop Aborted %s\n", COleDateTime::GetCurrentTime().Format() ).c_str());


		  }

	  }
	  //Handles Win32 exceptions (C structured exceptions) as C++ typed exceptions
	  static void trans_func( unsigned int u, EXCEPTION_POINTERS* pExp )
	  {
		  OutputDebugString( StdStringFormat("ResetAtMidnightThread  trans_func - Code = 0x%x\n",  pExp->ExceptionRecord->ExceptionCode).c_str() );
		  throw std::exception();
	  }
	  static UINT __stdcall  ResetAtMidnightThread(void *oObject)
	  {

		  try {

			  if (!oObject) return NULL;
			  AgentConfigurationEx *agent = static_cast <AgentConfigurationEx*> (oObject);
		  	_set_se_translator( trans_func );   //Handles Win32 exceptions (C structured exceptions) as C++ typed exceptions

			  COleDateTime now = COleDateTime::GetCurrentTime();
			  COleDateTime date2 =  COleDateTime(now.GetYear(), now.GetMonth(), now.GetDay(), 0, 0, 0) +  COleDateTimeSpan(1, 0, 0, 0);
			  //COleDateTime date2 =  now +  COleDateTimeSpan(0, 0, 1, 0);
			  OutputDebugString(StdStringFormat( "MTConnect Agent Service Will Reset at %s\n", date2.Format() ).c_str());
			  while(agent->_bRunning)
			  {
				  // Detect midnite and reset OPC connection
				  now = COleDateTime::GetCurrentTime();
				  if (now > date2)
				  {
					  COleDateTime date2 =  COleDateTime(now.GetYear(), now.GetMonth(), now.GetDay(), 0, 0, 0) +  COleDateTimeSpan(1, 0, 0, 0);
					  OutputDebugString(StdStringFormat("OPC Resetting to clear COM at  Date2=%s\n", date2.Format()).c_str());
					  agent->_bRunning=false;
				  }
				  ::Sleep(1000);

			  }
			 OutputDebugString(StdStringFormat( "MTConnect Agent Service Reset %s\n", COleDateTime::GetCurrentTime().Format() ).c_str());
			 // Report as error so SCM will restart - most SCM improvements post-XP DOES NOT WORK
			 //ReportSvcStatus(SERVICE_RUNNING, -1, 0); // no help

#if 1
			  STARTUPINFO si;
			  PROCESS_INFORMATION pi;
			  ZeroMemory( &si, sizeof(si) );
			  si.cb = sizeof(si);
			  ZeroMemory( &pi, sizeof(pi) );

			  // this assumes ping installed - not always true in windows 7
			  //std::string cmd = StdStringFormat("cmd /c net stop \"%s\" & ping 1.1.1.1 -n 1 -w 3000 > nul & net start \"%s\"", agent->mName.c_str(), agent->mName.c_str());        // Command line
			  std::string cmd = StdStringFormat("cmd /c net stop \"%s\" & net start \"%s\"", agent->mName.c_str(), agent->mName.c_str());        // Command line

			  CreateProcess( NULL,   // No module name (use command line)
				  const_cast<char *>(cmd.c_str()),
				  NULL,           // Process handle not inheritable
				  NULL,           // Thread handle not inheritable
				  FALSE,          // Set handle inheritance to FALSE
				  0,              // No creation flags
				  NULL,           // Use parent's environment block
				  NULL,           // Use parent's starting directory 
				  &si,            // Pointer to STARTUPINFO structure
				  &pi );           // Pointer to PROCESS_INFORMATION structure

			  ::Sleep(5000); 
#endif
		  }
		  catch(...)
		  {
			  OutputDebugString("Exception  - ResetAtMidnightThread(void *oObject)\n");
		  }
		  return 0;
	  }
	  ////////////////////////////////////////////////////////////////////
#ifdef OPC
	  bool _bOPCEnabled;
	  std::vector<CMachineAdapter *> machines;
#endif
	  config_reader::kernel_1a reader;
	  bool _bResetAtMidnight;
	  CHandle _hThread;
	  unsigned int _threadID;
	  bool _bRunning;
	  COleDateTime now ;
};
//int main(int aArgc, const char *aArgv[])
//{
//#ifdef WINDOWS
//	// MICHALOSKI ADDED
//	TCHAR buf[1000];
//	GetModuleFileName(NULL, buf, 1000);
//	std::string path(buf);
//	path=path.substr( 0, path.find_last_of( '\\' ) +1 );
//	SetCurrentDirectory(path.c_str());
//#endif
//	AgentConfigurationEx config;
//
//	return config.main(aArgc, (const char **) aArgv);
//}



int bWaitTilDone=0;

#pragma comment(linker, "/SUBSYSTEM:WINDOWS")
#pragma warning(disable: 4247) //warning C4297: 'WinMain' : function assumed not to throw an exception but does

int APIENTRY WinMain(HINSTANCE hInstance,
					 HINSTANCE hPrevInstance,
					 LPTSTR    lpCmdLine,
					 int       nCmdShow)
{
	try 
	{	
		OutputDebugString(StdStringFormat( "MTConnect Agent Service Entered %s\n" , nowtimestamp().c_str() ).c_str());
		AgentConfigurationEx config;

		//READY, ACTIVE, INTERRUPTED, or STOPPED 
		// Version 0.9 EXECUTION IDLE, EXECUTING, or PAUSED
		config_reader::kernel_1a reader(std::ifstream ((ExeDirectory() + INI_FILENAME).c_str()));
		std::vector<std::string> keys;
		//if (reader.is_block_defined("EnumMappings"))
		//{
		//	reader.block("EnumMappings").get_keys(keys);
		//	for(int i=0; i< keys.size(); i++)
		//		Adapter::enummapping[keys[i]]=reader.block("EnumMappings")[keys[i]];
		//	keys.clear();
		//	reader.block("TagMappings").get_keys(keys);
		//	for(int i=0; i< keys.size(); i++)
		//		Adapter::keymapping[keys[i]]=reader.block("TagMappings")[keys[i]];
		//}
		//else
		//{
		//	//Adapter::enummapping["execution.READY"]="IDLE";
		//	//Adapter::enummapping["execution.ACTIVE"]="EXECUTING";
		//	//Adapter::enummapping["execution.INTERRUPTED"]="PAUSED";
		//	//Adapter::enummapping["execution.STOPPED"]="PAUSED";
		//	//Adapter::keymapping["mode"]="controllermode";
		//	//Adapter::keymapping["Fovr"]="path_feedrateovr";
		//	//Adapter::keymapping["Fact"]="path_feedratefrt";
		//}
#ifdef WINDOWS
		// MICHALOSKI ADDED
		TCHAR buf[1000];
		GetModuleFileName(NULL, buf, 1000);
		std::string path(buf);
		path=path.substr( 0, path.find_last_of( '\\' ) +1 );
		SetCurrentDirectory(path.c_str());
#endif	

		config.configfile() = ExeDirectory() + INI_FILENAME;

		OutputDebugString(StdStringFormat( "MTConnect Agent Service Started %s\n" , nowtimestamp().c_str() ).c_str());
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
		OutputDebugString(StdStringFormat( "Enter config.main %s\n" , nowtimestamp().c_str() ).c_str());
		config.main( __argc,(const char **) __argv );
		// If this thread quits all other threads quit (unlike C#)
		while(bWaitTilDone)
		{
			::Sleep(1000);
		}

	}
	catch(std::exception e)
	{
		OutputDebugString(e.what());
		sLogger << LFATAL  << e.what() << "\n";
	}
	catch(...)
	{
		OutputDebugString("Service terminated abnormally in main\n");
		sLogger << LFATAL  << "Service terminated abnormally in main\n";
	}
	::CoUninitialize();
	OutputDebugString(StdStringFormat( "MTConnect Agent Service Ended %s\n" , nowtimestamp().c_str()).c_str());
	return -1;
}