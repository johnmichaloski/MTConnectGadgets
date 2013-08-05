//
// RunProcess.h
//

// Creating a Child Process with Redirected Input and Output

#pragma once
#include <windows.h> 
#include <tchar.h>
#include <stdio.h> 
#include <strsafe.h>
#include <string.h>
#include <sstream>
#include <boost/thread/mutex.hpp>

#define BUFSIZE 4096 

/** Example:
	CFindRemoteProcess shell;
		if(_gszCncControllerProcessName.size()>0)
		{
			if(!shell.FindExeProcess(_gszCncControllerProcessName, _gszTaskListCmd))
				throw StdStringFormat( _T("WARNING: Controller %s not running\n"), _opcservermachine.c_str());
		}
*/

class RedirectedIOProcess
{
	HANDLE g_hChildStd_IN_Rd ;
	HANDLE g_hChildStd_IN_Wr ;
	HANDLE g_hChildStd_OUT_Rd;
	HANDLE g_hChildStd_OUT_Wr;
public:
	PROCESS_INFORMATION piProcInfo; 
	STARTUPINFO siStartInfo;

	std::stringstream outbuffer;
	RedirectedIOProcess()
	{
		g_hChildStd_IN_Rd = NULL;
		g_hChildStd_IN_Wr = NULL;
		g_hChildStd_OUT_Rd = NULL;
		g_hChildStd_OUT_Wr = NULL;
	}
	~RedirectedIOProcess()
	{
		CloseHandle(piProcInfo.hProcess);
		CloseHandle(piProcInfo.hThread);
	}

	void CreateChildProcess(const TCHAR *argv); 
	void ReadFromPipe(void); 
	void ErrorExit(PTSTR); 
	void WriteToPipe(std::string chBuf) ;

	std::string RunProcess(const TCHAR *argv, std::string buffer="") 
	{ 
		SECURITY_ATTRIBUTES saAttr; 

		// Set the bInheritHandle flag so pipe handles are inherited. 

		saAttr.nLength = sizeof(SECURITY_ATTRIBUTES); 
		saAttr.bInheritHandle = TRUE; 
		saAttr.lpSecurityDescriptor = NULL; 

		// Create a pipe for the child process's STDOUT. 

		if ( ! CreatePipe(&g_hChildStd_OUT_Rd, &g_hChildStd_OUT_Wr, &saAttr, 0) ) 
			ErrorExit(TEXT("StdoutRd CreatePipe")); 

		// Ensure the read handle to the pipe for STDOUT is not inherited.

		if ( ! SetHandleInformation(g_hChildStd_OUT_Rd, HANDLE_FLAG_INHERIT, 0) )
			ErrorExit(TEXT("Stdout SetHandleInformation")); 

		// Create a pipe for the child process's STDIN. 

		if (! CreatePipe(&g_hChildStd_IN_Rd, &g_hChildStd_IN_Wr, &saAttr, 0)) 
			ErrorExit(TEXT("Stdin CreatePipe")); 

		// Ensure the write handle to the pipe for STDIN is not inherited. 

		if ( ! SetHandleInformation(g_hChildStd_IN_Wr, HANDLE_FLAG_INHERIT, 0) )
			ErrorExit(TEXT("Stdin SetHandleInformation")); 

		// Create the child process. 
		CreateChildProcess(argv);
#if 0
	DWORD dwRead, dwWritten, dwLeft, dwAvail; 
	CHAR chBuf[BUFSIZE+1]; 
		// Read from pipe that is the standard output for child process. 
		ReadFile( g_hChildStd_OUT_Rd, chBuf, BUFSIZE, &dwRead, NULL);
#endif
		if(buffer.size() >0)
			WriteToPipe(buffer);

		// Read from pipe that is the standard output for child process. 
		ReadFromPipe(); 
		return outbuffer.str(); 
	} 
};
inline void RedirectedIOProcess::CreateChildProcess(const TCHAR *argv)
// Create a child process that uses the previously created pipes for STDIN and STDOUT.
{ 
	TCHAR  szCmdline[1028];
	BOOL bSuccess = FALSE; 
  
	_stprintf( szCmdline, _T("%s"), argv );

	// Set up members of the PROCESS_INFORMATION structure. 

	ZeroMemory( &piProcInfo, sizeof(PROCESS_INFORMATION) );

	// Set up members of the STARTUPINFO structure. 
	// This structure specifies the STDIN and STDOUT handles for redirection.

	ZeroMemory( &siStartInfo, sizeof(STARTUPINFO) );
	siStartInfo.cb = sizeof(STARTUPINFO); 
	siStartInfo.hStdError = g_hChildStd_OUT_Wr;
	siStartInfo.hStdOutput = g_hChildStd_OUT_Wr;
	siStartInfo.hStdInput = g_hChildStd_IN_Rd;
	siStartInfo.dwFlags |= STARTF_USESTDHANDLES|STARTF_USESHOWWINDOW;
	siStartInfo.wShowWindow = SW_HIDE;

	// Create the child process. 

	bSuccess = CreateProcess(NULL, 
		szCmdline,     // command line 
		NULL,          // process security attributes 
		NULL,          // primary thread security attributes 
		TRUE,          // handles are inherited 
		0,             // creation flags 
		NULL,          // use parent's environment 
		NULL,          // use parent's current directory 
		&siStartInfo,  // STARTUPINFO pointer 
		&piProcInfo);  // receives PROCESS_INFORMATION 

	// If an error occurs, exit the application. 
	if ( ! bSuccess ) 
		ErrorExit(TEXT("CreateProcess"));
}

inline void RedirectedIOProcess::WriteToPipe(std::string chBuf) 
{ 
   DWORD  dwWritten; 
   BOOL bSuccess = FALSE;
   bSuccess = WriteFile(g_hChildStd_IN_Wr, chBuf.c_str(), chBuf.size(), &dwWritten, NULL);
} 
inline	void RedirectedIOProcess::ReadFromPipe(void) 
{ 
// Read output from the child process's pipe for STDOUT
// and write to the parent process's pipe for STDOUT. 
// Stop when there is no more data. 

	DWORD dwRead, dwLeft, dwAvail; 
	CHAR chBuf[BUFSIZE+1]; 
	BOOL bSuccess = FALSE;

	for (;;) 
	{ 
		bSuccess = ReadFile( g_hChildStd_OUT_Rd, chBuf, BUFSIZE, &dwRead, NULL);

		if( ! bSuccess || dwRead == 0 ) break; 
		chBuf[dwRead]=0;
		outbuffer << chBuf;
		OutputDebugString(chBuf);
		//if( WAIT_OBJECT_0==WaitForSingleObject( piProcInfo.hProcess, 100 ))
		//	break;
		
		// We don't expect more data, and its not an ongoing thing
		bSuccess = PeekNamedPipe(g_hChildStd_OUT_Rd, NULL, 0, &dwRead, &dwAvail, &dwLeft);
		if(! bSuccess || dwAvail==0 && WAIT_OBJECT_0==WaitForSingleObject( piProcInfo.hProcess, 100 ))
			break;

	} 
} 

inline void RedirectedIOProcess::ErrorExit(PTSTR lpszFunction) 
{ 
// Format a readable error message, display a message box, 
// and exit from the application.

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

	lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, 
		(lstrlen((LPCTSTR)lpMsgBuf)+lstrlen((LPCTSTR)lpszFunction)+40)*sizeof(TCHAR)); 
	StringCchPrintf((LPTSTR)lpDisplayBuf, 
		LocalSize(lpDisplayBuf) / sizeof(TCHAR),
		TEXT("%s failed with error %d: %s"), 
		lpszFunction, dw, lpMsgBuf); 

	LocalFree(lpMsgBuf);
	LocalFree(lpDisplayBuf);
	throw std::exception((LPCTSTR)lpDisplayBuf); 
}

class CFindRemoteProcess
{
	RedirectedIOProcess * shell;
public:
	CFindRemoteProcess() {shell  = new RedirectedIOProcess(); }
	~CFindRemoteProcess() { Kill(); }
	std::string ExeSsh(std::string cmd, std::string pw)
	{
		std::string output;
		output=shell->RunProcess(cmd.c_str(),pw);
		OutputDebugString(output.c_str());
		return output;
	}
	void Kill () 
	{    
		TerminateProcess(shell->piProcInfo.hProcess,0);
		if(shell!=NULL)
			delete shell;
	}
};
class CFactorySpinUp
{
public:
	std::vector<int> shdrPorts;
	std::vector<std::string> devicenames;
	std::vector<std::string> ipDeviceAgents;
	std::vector<std::string> ipCmdAgents;
	std::vector<std::string> ipMachines;
	std::vector<CFindRemoteProcess> remoteProcess;
	boost::condition_variable * _cond;
	boost::mutex	_access;

	CFactorySpinUp( boost::condition_variable *cond ) : _cond(cond)
	{

	}
	void StopAll()
	{
		for(int i=0; i< remoteProcess.size(); i++)
			remoteProcess[i].Kill();
		remoteProcess.clear();
	}
	void Clear()
	{
		ipMachines.clear();
		shdrPorts.clear();
		devicenames.clear();
		ipDeviceAgents.clear();
		ipCmdAgents.clear();
	}
	//–s pluto –m M1 –p 7878 –c pluto
	void AddDevice(std::string laptop, std::string devicename, std::string ipDeviceAgent, int shdrPort, std::string ipCmdAgent)
	{
		ipMachines.push_back(laptop);
		shdrPorts.push_back(shdrPort);
		devicenames.push_back(devicename);
		ipDeviceAgents.push_back(ipDeviceAgent);
		ipCmdAgents.push_back(ipCmdAgent);
	}
	void StartSpinUp()
	{
		boost::mutex::scoped_lock lock(_access);
		_cond->wait(lock);

		for(int i=0; i< shdrPorts.size(); i++)
		{
			remoteProcess.push_back(CFindRemoteProcess());

			std::string ssh = StdStringFormat("ssh  simuser@%s -i \"/cygdrive/c/Documents and Settings/simuser/My Documents/.ssh/id_rsa\"  ", 
				ipMachines[i].c_str());
			std::string cmd = StdStringFormat(" /usr/local/proj/gomotion/bin/spinup -s %s -p %d -m %s -c %s", 
				ipDeviceAgents[i].c_str(),
				shdrPorts[i],
				devicenames[i].c_str(),
				ipCmdAgents[i].c_str()
				);

			remoteProcess.back().ExeSsh(ssh +  cmd, "password1\n");
		}
	}
};