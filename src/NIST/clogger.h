// **************************************************************************
// CLogger.h 
//
// Description:
//
// DISCLAIMER:
// This software was developed by U.S. Government employees as part of
// their official duties and is not subject to copyright. No warranty implied 
// or intended.
// **************************************************************************

#pragma once
#include "atlstr.h"
#include <fstream>
#include <iostream>
#include "StdStringFcn.h"


#ifdef LOGLISTENERS
// This is for notifying listeners to logged messages - mnany to many relationship
#include <boost/function.hpp> 
#include <boost/function_equal.hpp> 
typedef boost::function<void (const TCHAR * msg)> FcnLognotify;
#include <vector>

#endif
// This is useful for preventing endless repeated error messages 
#define LOGONCE  static long nLog##__LINE__=0; if( 0 == nLog##__LINE__++) 
//#define LOGONCE  


/** Allow redirectd of std::cout to vc console output
		std::cout.rdbuf(&Logger);
		std::cout << "Hello World\n";
		std::cout.flush();
*/

class Fstream
{
public:

	std::fstream fp;

	Fstream(const char * filename)
	{
		//fp.open (filename, std::fstream::out );
		fp.open(filename, std::fstream::out, OF_SHARE_DENY_NONE);
	}

	~Fstream() {  fp.close();}
};

class basic_debugbuf : public std::streambuf
{
public:
	basic_debugbuf(int bufferSize=100) 
	{
		if (bufferSize)
		{
			char *ptr = new char[bufferSize];
			setp(ptr, ptr + bufferSize);
		}
		else
			setp(0, 0);
	}
	virtual ~basic_debugbuf() 
	{
		sync();
		delete[] pbase();
	}

    virtual void writeString(const std::string &str)
    {
        OutputDebugString(str.c_str());
    }

private:
    int	overflow(int c)
    {
        sync();

        if (c != EOF)
        {
            if (pbase() == epptr())
            {
                std::string temp;
                temp += char(c);
                writeString(temp);
            }
            else
                sputc(c);
        }

        return 0;
    }

    int	sync()
    {
        if (pbase() != pptr())
        {
            int len = int(pptr() - pbase());
            std::string temp(pbase(), len);
            writeString(temp);
			OutputDebugString(temp.c_str());
            setp(pbase(), epptr());
        }
        return 0;
    }
   
};
class DebugStream
	: public basic_debugbuf
{
public:
	Fstream _stream;
	DebugStream(std::string filename) : _stream (filename.c_str())
	{

	}
	virtual void writeString(const std::string &str)
	{
		 _stream.fp << str;
	}

};
#if 1
/**
FIXME: add timestamp to front header

*/
struct nullstream: std::fstream {
nullstream(): std::ios(0),  std::fstream((_Filet *) NULL) {}
};
namespace Logging
{
 __declspec(selectany)  	  int FATAL=-1;
 __declspec(selectany)  	  int ZERROR=0;
 __declspec(selectany)  	  int WARNING=1;
 __declspec(selectany)  	  int INFORMATION=2;
 __declspec(selectany)  	  int LIGHTDEBUG=3;
 __declspec(selectany)  	  int HEAVYDEBUG=5;

};

class CLogger : public basic_debugbuf
{
public:
	
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

    virtual void writeString(const std::string &str)
    {
       LogMessage(str.c_str(),-1);
    }



#ifdef LOGLISTENERS
	void AddListener(FcnLognotify notify)
	{
		listeners.push_back(notify);
	}
#endif
#ifdef DEBUG
	int Debug(const TCHAR * msg){ return LogErrorMessage(msg,Logging::LIGHTDEBUG); }
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
 		try{
			DebugFile.clear();
	   // DebugFile.exceptions ( std::fstream::failbit | std::fstream::badbit );
		DebugFile.open(filename.c_str(), opMode, OF_SHARE_DENY_NONE);
		}catch(std::exception e)
		{
			OutputDebugString("Logger Debug File bad");
			OutputDebugString(e.what());

		}
		if(DebugFile.bad())
		{
			OutputDebugString("Logger Debug File bad\n");
		}

	}
	void LogMessage(std::string msg, int level)
	{
		if( DebugLevel() < level)
			return;
	
		OutputDebugString(msg.c_str());

		if(!DebugFile.is_open())
			return;
		if(Timestamping())
			DebugFile << Timestamp();
		DebugFile << msg;
#ifdef LOGLISTENERS
		for(int i=0; i< listeners.size(); i++)
			listeners[i](msg);
#endif
		DebugFile.flush();
	}
	/**
	Logger.Open(::ExeDirectory() + "debug.txt");
	Logger() << "Hello World\n";
	Logger().flush();
	Logger().close();
	*/
	std::fstream & operator() (void) { return this->DebugFile; }
	std::fstream & operator() (int level) 
	{ 
		DebugFile.flush();
		if( DebugLevel() < level)
			return this->devnull;
		return this->DebugFile; 
	}


	int Log(std::string msg)
	{
		LogMessage(msg.c_str(),  -1);
		return 0;
	}

	int LogErrorMessage(const TCHAR * msg, int level)
	{
		LogMessage(msg,  level);
		return -1;
	}
	int & DebugLevel() { return _debuglevel; }
	bool & Timestamping() { static bool bTimestamp=false;  return  bTimestamp; }
	int _debuglevel;
	int Fatal(const TCHAR * msg){ return LogErrorMessage(msg,Logging::FATAL); }
	int Error(const TCHAR * msg){ return LogErrorMessage(msg,Logging::ZERROR); }
	int Warning(const TCHAR * msg){return  LogErrorMessage(msg,Logging::WARNING); }
	int Info(const TCHAR * msg){ return LogErrorMessage(msg,Logging::INFORMATION); }
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
	nullstream devnull;
#ifdef LOGLISTENERS
	std::vector<FcnLognotify> listeners;
#endif
};
 
#endif

__declspec(selectany)  CLogger GLogger;
