//
// Logger.h 
//

// This software was developed by U.S. Government employees as part of
// their official duties and is not subject to copyright. No warranty implied 
// or intended.

#pragma once
#include "atlstr.h"
#include <fstream>

// This is for notifying listeners to logged messages - mnany to many relationship
#include <boost/function.hpp> 
#include <boost/function_equal.hpp> 
typedef boost::function<void (const TCHAR * msg)> FcnLognotify;
#include <vector>
#include "StdStringFcn.h"

// AddListener(boost::bind(&CMainDlg::ProgramChangeMonitor, this,_1));
// This is useful for preventing endless repeated error messages 
#define LOGONCE  static long nLog##__LINE__=0; if( 0 == nLog##__LINE__++) 
//#define LOGONCE  


/**
FIXME: add timestamp to front header

*/
class CLogger
{
public:
	static const int FATAL=-1;
	static const int LERROR=0;
	static const int WARNING=1;
	static const int INFORMATION=2;
	static const int LDEBUG=3;
	static const int HEAVYDEBUG=5;
	
	CLogger()
	{
		DebugLevel()=0;
		filename=::ExeDirectory() + "debug.txt";
	}
	~CLogger()
	{
		if(DebugFile.is_open())
			DebugFile.close();
	}

	void AddListener(FcnLognotify notify)
	{
		listeners.push_back(notify);
	}

#ifdef DEBUG
	int Debug(const TCHAR * msg){ return LogErrorMessage(msg,LDEBUG); }
#else
	// should be optimized out.
#define Debug(X) DebugLevel
#endif

	void Open(std::string filename, int bAppend=false)
	{
		this->filename=filename;
		Open(bAppend);
	}
	void Open(int bAppend)
	{	
		int opMode = std::fstream::out;
		if(bAppend)
			opMode |= std::fstream::app;

		DebugFile.open(filename.c_str(), opMode, OF_SHARE_DENY_NONE);
	}
	void LogMessage(const TCHAR * msg, int level)
	{
		if( DebugLevel() < level)
			return;
	
		OutputDebugString(msg);
		for(int i=0; i< listeners.size(); i++)
			listeners[i](msg);

		if(!DebugFile.is_open())
			return;
		if(Timestamping())
			DebugFile << Timestamp();
		DebugFile << msg;

		DebugFile.flush();
	}

	int LogErrorMessage(const TCHAR * msg, int level)
	{
		LogMessage(msg,  level);
		return -1;
	}
	int & DebugLevel() { static int _debuglevel=0; return _debuglevel; }
	bool & Timestamping() { static bool bTimestamp=false;  return  bTimestamp; }

	int Fatal(const TCHAR * msg){ return LogErrorMessage(msg,FATAL); }
	int Error(const TCHAR * msg){ return LogErrorMessage(msg,LERROR); }
	int Warning(const TCHAR * msg){return  LogErrorMessage(msg,WARNING); }
	int Info(const TCHAR * msg){ return LogErrorMessage(msg,INFORMATION); }
	/////////////////////////////////////////////////////////////////////////////

	static std::string Timestamp()
	{
		char aBuffer[32];
#ifdef WIN32
		SYSTEMTIME st;
		GetSystemTime(&st);
		sprintf(aBuffer, "%4d-%02d-%02dT%02d:%02d:%02d.%04dZ", st.wYear, st.wMonth, st.wDay, st.wHour, 
			st.wMinute, st.wSecond, st.wMilliseconds);
#else
		struct timeval tv;
		struct timezone tz;

		gettimeofday(&tv, &tz);

		strftime(aBuffer, 64, "%Y-%m-%dT%H:%M:%S", gmtime(&tv.tv_sec));
		sprintf(aBuffer + strlen(aBuffer), ".%06dZ", tv.tv_usec);
#endif
		return aBuffer;
	}
protected:
	std::fstream DebugFile;
	int nDebugReset;
	std::string filename;
	std::vector<FcnLognotify> listeners;

};
 __declspec(selectany)  CLogger Logger;

