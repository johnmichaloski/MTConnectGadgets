//
// MTCAgentCmdE.cpp 
//

// This software was developed by U.S. Government employees as part of
// their official duties and is not subject to copyright. No warranty implied 
// or intended.


#include "StdAfx.h"
#include "MTCAgentCmd.h"
#include "agent.hpp"

//#pragma comment(lib, "agent.lib")
//#pragma comment( lib, "msxml2.lib" )

#include "sys/stat.h"
#include "string.h"
#include "fcntl.h"

#include "Shellapi.h"

//#include "dlib/config_reader.h"
#include <dlib/logger.h>

#include "NIST/Config.h"
#include "NIST/StdStringFcn.h"
//#include "CLogger.h"
#include "NIST/Logger.h"
#include "NIST/AgentCfg.h"
#include "NIST/RunProcess.h"
int AgentMgr::_debugSimulation=0;	
static std::string GetHostName()
{
	char hostname[1024];
	hostname[1023] = '\0';
	gethostname(hostname, 1023);
//	printf("Hostname: %s\n", hostname);
	//struct hostent* h;
	//h = gethostbyname(hostname);
	//return h->h_name;
	return hostname;
}

template<class Seq> void purge(Seq& c) 
{
	typename Seq::iterator i;
	for(i = c.begin(); i != c.end(); ++i) {
		delete *i;
		*i = 0;
	}
}

using namespace std;
using namespace dlib;

static void trans_func( unsigned int u, EXCEPTION_POINTERS* pExp )
{
	std::string errmsg =  StdStringFormat("COpcAdapter In trans_func - Code = 0x%x\n",  pExp->ExceptionRecord->ExceptionCode);
	OutputDebugString(errmsg.c_str() );
	throw std::exception(errmsg.c_str() , pExp->ExceptionRecord->ExceptionCode);
} 


//static logger sLogger("main");
//static   const log_level LENTRY(400,"ENTRY");

static const char INI_FILENAME[] = "agent.cfg";
static const char LOG_FILENAME[] = "errors.log";


#include "NIST/CMSDIntegrator.h"

AgentMgr::AgentMgr() : spinup(&cond)
{
	_group = NULL;
	_agent = NULL;
}
CResourceHandler * AgentMgr::findResource(std::string id)
{
	for(int i=0; i< _resourceHandlers.size(); i++)
		if(_resourceHandlers[i]->_identifier == id)
			return _resourceHandlers[i];
		return NULL;
}

CCellHandler * AgentMgr::findCell(std::string id)
{
	for(int i=0; i< _cellHandlers.size(); i++)
		if(_cellHandlers[i]->_cell->identifier == bstr_t(id.c_str()))
			return _cellHandlers[i];
		return NULL;
}

//CJobHandler * AgentMgr::findJob(std::string id)
//{
//	for(int i=0; i< _jobHandlers.size(); i++)
//		if(_jobHandlers[i]->_job->identifier == bstr_t(id.c_str()))
//			return _jobHandlers[i];
//		return NULL;
//}
//CPartHandler * AgentMgr::findPart(std::string id)
//{
//	for(int i=0; i< _partHandlers.size(); i++)
//		if(_partHandlers[i]->_part->identifier == bstr_t(id.c_str()))
//			return _partHandlers[i];
//		return NULL;
//}
//CProcessPlanHandler * AgentMgr::findProcessPlan(std::string id)
//{
//	for(int i=0; i< _processPlanHandlers.size(); i++)
//		if(_processPlanHandlers[i]->_processplan->identifier == bstr_t(id.c_str()))
//			return _processPlanHandlers[i];
//		return NULL;
//}

void AgentMgr::clear()
{

	cmsd.Clear();
	_cmdAgentCfg.Clear();
	_devicesAgentCfg.Clear();
	config.Clear();
	purge(_resourceHandlers);
	purge(_cellHandlers);
	//purge(_jobHandlers);
	//purge(_partHandlers);
	//purge(_processPlanHandlers);

	_resourceHandlers.clear();
	_cellHandlers.clear();
	///_jobHandlers.clear();
	//_partHandlers.clear();
	//_processPlanHandlers.clear();
	spinup.Clear();

	delete _group;
	delete _agent;

}

int AgentMgr::thread(int aArgc, const char *aArgv[])
{
	//sLogger << LENTRY  << "MTConnect Agent Service Started " << nowtimestamp() << "\n";

#ifdef OBSERVER
	// Test out observer functionality
	Device *dev = getDeviceByName(devicename);
	DataItem *di = dev->getDeviceDataItem("Xabs");
	di->addObserver(new  BusyObserver("Xabs", di));
#endif
	try{

		clear();
		_group= new boost::thread_group();
		_agent = new AgentConfiguration();

		int nPort=7878;
		std::string cfgfile;
		if(aArgc > 0)
		{
			cfgfile= aArgv[0];
		}
		else
			cfgfile= ::ExeDirectory() + "VirtualFactoryTestbed.xml";
		
		char result[ MAX_PATH ];
		std::string path( result, GetModuleFileName( NULL, result, MAX_PATH ) );
		std::string inifile =  path.substr(0,path.find_last_of(".")) + ".ini";


		if(GetFileAttributesA(inifile.c_str())== INVALID_FILE_ATTRIBUTES)
			throw std::exception(("No " + inifile + " file").c_str());
		config.load(inifile);
		_devicexmlpath =  config.GetSymbolValue("CONFIG.DevicesFolder", ::ExeDirectory()).c_str();
		_devicefile =  config.GetSymbolValue("CONFIG.DevicesFile", "Devices.xml").c_str();
		_cfgfile =  config.GetSymbolValue("CONFIG.CfgFile","Agent.cfg").c_str();
		_httpPort =  config.GetSymbolValue("CONFIG.HttpPort","81").toNumber<int>();
		_debugSimulation =  config.GetSymbolValue("CONFIG.DebugSimulation","1").toNumber<int>();
		_cmdAgentCfg.SetDevicesXmlFolder(_devicexmlpath);
		_cmdAgentCfg.SetHttpPort(_httpPort);
		_cmdAgentCfg.SetXmlFile(_devicefile);
		_cmdAgentCfg.SetCfgFile(_cfgfile);
		_cmdAgentCfg.SetDestinationFolder(::ExeDirectory());
		SetCurrentDirectory(::ExeDirectory().c_str()); // fixes Agent file lookup issue

	
	//	if( GetFileAttributesA(cfgfile.c_str())!= INVALID_FILE_ATTRIBUTES)
		{
			for(int i=0 ; i< cmsd.resources->size(); i++)
			{
				Resource * r = (Resource *) cmsd.resources->at(i).get();
				std::string name = (LPCSTR) r->name;
				if(name.empty() || name == "None")  // something wrong
					continue; 

				_cmdAgentCfg.AddDevice(name,  // M1, M2
					"Command", // lookup name in devices.xml folder
					"",  // no ip required for SHDR, will talk directly to agent
					"0");			//writing to agent will be done using thread pointer not SHDR

				_devicesAgentCfg.AddDevice(name,  // M1, M2
					"Generic", // lookup name in devices.xml folder
					"127.0.0.1", 
					StdStringFormat("%d", nPort++));

				//spinup.AddDevice("herbie",
				//	name,
				//	GetHostName(),
				//	nPort-1,
				//	GetHostName() + ":81"
				//	);

				CResourceHandler *  _resourceHandler = new CResourceHandler(_agent, this,r, &cmsd);
				_resourceHandlers.push_back(_resourceHandler);
				_resourceHandlers.back()->Configure( config,(LPCSTR) r->identifier,  name, "Command", "127.0.0.1:80/"+name,_devicexmlpath);

			}

			for(int i=0 ; i< cmsd.cells->size(); i++)
			{
				Cell * c = (Cell *) cmsd.cells->at(i).get();
				std::string name = (LPCSTR) c->name;
				CCellHandler *  _cellHandler = new CCellHandler((AgentMgr * ) this, c,&cmsd);
				_cellHandlers.push_back(_cellHandler);
				for(int j=0; j< c-> resourceIds.size(); j++)
				{
					CResourceHandler * r  =  findResource((LPCSTR) c-> resourceIds[j]) ;
					if(r!=NULL)
						_cellHandler->_resources.push_back(r);
				}
			}
		}
		_cmdAgentCfg.Start(_agent);
		::Sleep(1000);

		/*for(int i=0; i< _resourceHandlers.size(); i++)
			_group->create_thread(boost::bind(&CResourceHandler::Thread, _resourceHandlers[i]));
*/
	/*	for(int i=0 ; i< cmsd.jobs->size(); i++)
		{		
			CJobHandler *  _jobHandler = new CJobHandler((AgentMgr * ) this, (Job*) cmsd.jobs->at(i).get(),&cmsd,_cellHandlers);
			_jobHandlers.push_back(_jobHandler);
			_group->create_thread(boost::bind(&CJobHandler::Cycle, _jobHandler));
		}
*/
		_nSpinup =  config.GetSymbolValue("CONFIG.Spinup",0).toNumber<int>();
		if(_nSpinup)
		{
			_devicesAgentCfg.SetDevicesXmlFolder(_devicexmlpath);
			_devicesAgentCfg.SetHttpPort(80);
			_devicesAgentCfg.SetXmlFile("Devices1.xml");
			_devicesAgentCfg.SetCfgFile("Agent1.cfg");
			_devicesAgentCfg.SetDestinationFolder(::ExeDirectory());
			_devicesAgentCfg.SpawnProcess();
			spinup.StartSpinUp();
		}
		start();
	}
	catch(...) {}

	return 0;
}
// Start the server. This blocks until the server stops.
void AgentMgr::start()
{
	::Sleep(5000);
	cond.notify_all();  
	//_agent->start();
}
void AgentMgr::stop()
{
	for(int i=0; i< _resourceHandlers.size(); i++)
		_resourceHandlers[i]->Stop();

	_group->join_all();
	spinup.StopAll();
	_agent->stop();
}
