// MazakAgent.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <exception>
#include "NIST/Logger.h"
#include "StdStringFcn.h"

#include "atlutil.h"
#include "ATLComTime.h"

#include "agent.hpp"
#include "config.hpp"

#pragma comment(lib, "Ws2_32.lib")
static const char INI_FILENAME[] = "agent.cfg";



#if defined(WIN64) && defined( _DEBUG) 
#pragma message( "DEBUG x64" )
#pragma comment(lib, "libxml2_64d.lib")
#pragma comment(lib, "libboost_system-vc100-mt-sgd-1_53.lib")
#pragma comment(lib, "libboost_thread-vc100-mt-sgd-1_53.lib")
  
#elif !defined( _DEBUG) && defined(WIN64)
#pragma message( "RELEASE x64" )
#pragma comment(lib, "libxml2_64.lib")
#pragma comment(lib, "libboost_thread-vc100-mt-s-1_53.lib")
#pragma comment(lib, "libboost_system-vc100-mt-s-1_53.lib")

#elif defined(_DEBUG) && defined(WIN32)
#pragma message( "DEBUG x32" )
#pragma comment(lib, "libxml2d.lib")
#pragma comment(lib, "libboost_thread-vc100-mt-sgd-1_53.lib")
#elif !defined( _DEBUG) && defined(WIN32)
#pragma message( "RELEASE x32" )
#pragma comment(lib, "libboost_thread-vc100-mt-s-1_53.lib")
#pragma comment(lib, "libxml2.lib")
#endif


#include <strsafe.h>
void ReportError(LPTSTR lpszFunction) 
{ 
	// Retrieve the system error message for the last-error code

	LPVOID lpMsgBuf;
	LPVOID lpDisplayBuf;
	DWORD dw = GetLastError(); 

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR) &lpMsgBuf,
		0, NULL );

	// Display the error message and exit the process

	lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, 
		(lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR)); 
	StringCchPrintf((LPTSTR)lpDisplayBuf, 
		LocalSize(lpDisplayBuf) / sizeof(TCHAR),
		TEXT("%s failed with error %d: %s"), 
		lpszFunction, dw, lpMsgBuf); 

	GLogger.Fatal(StdStringFormat("%s\n", lpDisplayBuf ));

	LocalFree(lpMsgBuf);
	LocalFree(lpDisplayBuf);
	ExitProcess(dw); 
}

extern SERVICE_STATUS          gSvcStatus; 
extern VOID ReportSvcStatus( DWORD dwCurrentState, //    The current state (see SERVICE_STATUS)
							DWORD dwWin32ExitCode, //   The system error code
							DWORD dwWaitHint); //    Estimated time for pending operation, 

static void trans_func( unsigned int u, EXCEPTION_POINTERS* pExp )
{
	GLogger.Fatal( StdStringFormat("AgentConfigurationEx::In trans_func - Code = 0x%x\n",  pExp->ExceptionRecord->ExceptionCode).c_str() );
#ifdef DEBUG
	DebugBreak();
#endif
	throw std::exception();
}

class AgentConfigurationEx : public AgentConfiguration
{
public:
	AgentConfigurationEx() : 
	  _bResetAtMidnight(true)	  
	  {
		  _bRunning=false;
	  }

	  CWorkerThread<> _resetthread;
	  struct CResetThread : public IWorkerThreadClient
	  {
		  HRESULT Execute(DWORD_PTR dwParam, HANDLE hObject);
		  HRESULT CloseHandle(HANDLE){ ::CloseHandle(_hTimer); return S_OK; }
		  HANDLE _hTimer;
	  } _ResetThread;



	  virtual void start()
	  {
		  GLogger.Fatal(StdStringFormat( "MTConnect Agent Service Start %s\n" , COleDateTime::GetCurrentTime().Format() ).c_str());
		  try{
			  //struct stat buf;
			  //std::string path = ExeDirectory() + INI_FILENAME;
			  //if (stat(path.c_str(), &buf) != 0) 
				 // throw std::exception(("Ini file doesn't exist " + path).c_str());

			  //reader.load_from(std::ifstream ((ExeDirectory() + INI_FILENAME).c_str()));

			  //_bResetAtMidnight = ConvertString<bool>(reader.block("OPCSERVER")["ResetAtMidnight"], true);
			  if(true)
			  {
				  GLogger.Fatal("Agent will Reset At Midnight\n");

				  COleDateTime now = COleDateTime::GetCurrentTime();
				  COleDateTime date2 =  COleDateTime(now.GetYear(), now.GetMonth(), now.GetDay(), 0, 0, 0) +  COleDateTimeSpan(1, 0, 0, 1);
				  //COleDateTime date2 =  now +  COleDateTimeSpan(0, 0, 2, 0); // testing reset time - 2 minutes
				  COleDateTimeSpan tilmidnight = date2-now;
				  _resetthread.Initialize();
				  _resetthread.AddTimer(
					  (long) tilmidnight.GetTotalSeconds() * 1000,
					  &_ResetThread,
					  (DWORD_PTR) this,
					  &_ResetThread._hTimer  // stored newly created timer handle
					  ) ;


			  }

			  //Handles Win32 exceptions (C structured exceptions) as C++ typed exceptions
			  //_set_se_translator( trans_func ); 

			  // Start the server. This blocks until the server stops.
			  AgentConfiguration::start();

		  }
		  catch(std::exception e)
		  {
			   GLogger.Fatal(StdStringFormat("AgentConfigurationEx::start() failed - %s\n", e.what()).c_str());
			  throw e;
		  }
		  catch(...) {}

	  }

	  virtual void stop()
	  {

		  int nWaitTime = 5000;
		  ReportSvcStatus(SERVICE_STOP_PENDING, 0, 15000);
		  StopAll();
		  ReportSvcStatus(SERVICE_STOP, 0, 0);
	  }

	  void StopAll()
	  {
		  try {

			   GLogger.Fatal(StdStringFormat( "MTConnect Agent Service Stopped %s\n", COleDateTime::GetCurrentTime().Format() ).c_str());
			  _resetthread.Shutdown();
			  // Check if invoked from SCM as opposed to midnite reset.
			  AgentConfiguration::stop();
			  //if( _hThread!=NULL && _bRunning)
			  //{
				 // BOOL  bTerminate= TerminateThread(_hThread, 0);
			  //}
		  }
		  catch(...)
		  {
			   GLogger.Fatal(StdStringFormat( "MTConnect Agent Service Stop Aborted %s\n", COleDateTime::GetCurrentTime().Format() ).c_str());
		  }

	  }
		  ////////////////////////////////////////////////////////////////////
	  config_reader::kernel_1a reader;
	  bool _bResetAtMidnight;
	  CHandle _hThread;
	  unsigned int _threadID;
	  bool _bRunning;
	  COleDateTime now ;
};





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

		GLogger.Open(::ExeDirectory() + "debug.txt");
		GLogger.DebugLevel()=5;
		GLogger.Timestamping()=true;
#ifdef DEBUG
		GLogger.OutputConsole()=true;
#endif
		//READY, ACTIVE, INTERRUPTED, or STOPPED 
		// Version 0.9 EXECUTION IDLE, EXECUTING, or PAUSED
#if 0
		config_reader::kernel_1a reader(std::ifstream ((ExeDirectory() + INI_FILENAME).c_str()));
		std::vector<std::string> keys;
		if (reader.is_block_defined("EnumMappings"))
		{
			reader.block("EnumMappings").get_keys(keys);
			for(int i=0; i< keys.size(); i++)
				Adapter::enummapping[keys[i]]=reader.block("EnumMappings")[keys[i]];
			keys.clear();
			reader.block("TagMappings").get_keys(keys);
			for(int i=0; i< keys.size(); i++)
				Adapter::keymapping[keys[i]]=reader.block("TagMappings")[keys[i]];
		}
		else
#endif
		{
			Adapter::enummapping["execution.READY"]="IDLE";
			Adapter::enummapping["execution.ACTIVE"]="EXECUTING";
			Adapter::enummapping["execution.INTERRUPTED"]="PAUSED";
			Adapter::enummapping["execution.STOPPED"]="PAUSED";
			Adapter::keymapping["mode"]="controllermode";
			Adapter::keymapping["Fovr"]="path_feedrateovr";
			Adapter::keymapping["Fact"]="path_feedratefrt";
		}
#ifdef _WINDOWS
		// MICHALOSKI ADDED
		TCHAR buf[1000];
		GetModuleFileName(NULL, buf, 1000);
		std::string path(buf);
		path=path.substr( 0, path.find_last_of( '\\' ) +1 );
		SetCurrentDirectory(path.c_str());
#endif	

		config.configfile() = ExeDirectory() + INI_FILENAME;

		 GLogger.Fatal(StdStringFormat( "MTConnect Agent Service Started %s\n" , nowtimestamp().c_str() ).c_str());
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
		 GLogger.Fatal(StdStringFormat( "Enter config.main %s\n" , nowtimestamp().c_str() ).c_str());
		config.main( __argc,(const char **) __argv );

	}
	catch(std::exception e)
	{
		 GLogger.Fatal(e.what());
	}
	catch(...)
	{
		 GLogger.Fatal("Service terminated abnormally in main\n");
	}
	::CoUninitialize();
	 GLogger.Fatal(StdStringFormat( "MTConnect Agent Service Ended %s\n" , nowtimestamp().c_str()).c_str());
	return -1;
}

HRESULT AgentConfigurationEx::CResetThread::Execute(DWORD_PTR dwParam, HANDLE hObject)
{
	static char name[] = "CResetThread::Execute";

	AgentConfigurationEx * agent = (AgentConfigurationEx*) dwParam;
	CancelWaitableTimer(hObject);

	try {
		//GLogger.LogMessage("MTConnect adapter Service Start Resetting %s\n", (LPCSTR) COleDateTime::GetCurrentTime());;
		//OutputDebugString(StdStringFormat( "MTConnect adapter Service Start Resetting %s\n" , (LPCSTR) COleDateTime::GetCurrentTime()).c_str());

		PROCESS_INFORMATION pi;
		ZeroMemory( &pi, sizeof(pi) );

		STARTUPINFO si;
		ZeroMemory( &si, sizeof(si) );
		si.cb = sizeof(si);
		si.dwFlags = STARTF_USESHOWWINDOW;
		si.wShowWindow = SW_HIDE;	 // set the window display to HIDE	

		// SCM reset command of this service 
		std::string cmd = StdStringFormat("cmd /c net stop \"%s\" & net start \"%s\"", agent->name().c_str(), agent->name().c_str());        // Command line

		if(!::CreateProcess( NULL,   // No module name (use command line)
			const_cast<char *>(cmd.c_str()),
			NULL,           // Process handle not inheritable
			NULL,           // Thread handle not inheritable
			FALSE,          // Set handle inheritance to FALSE
			0,              // No creation flags
			NULL,           // Use parent's environment block
			NULL,           // Use parent's starting directory 
			&si,            // Pointer to STARTUPINFO structure
			&pi ))           // Pointer to PROCESS_INFORMATION structure
			ReportError("CreateProcess ") ;

		::Sleep(1000); // make sure process has spawned before killing thread
	}
	catch(...)
	{
		 GLogger.Fatal(StdStringFormat( "Exception  - ResetAtMidnightThread(void *oObject)\n" ).c_str());
	}
	return S_OK;
}