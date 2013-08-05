//
// MTCAgentCmdE.cpp 
//

// This software was developed by U.S. Government employees as part of
// their official duties and is not subject to copyright. No warranty implied 
// or intended.


#include "StdAfx.h"
#include "MTCAgentCmd.h"
#include "agent.hpp"

#pragma comment(lib, "agent.lib")
#pragma comment( lib, "msxml2.lib" )

#include "sys/stat.h"
#include "string.h"
#include "fcntl.h"

#include "Shellapi.h"

//#include "dlib/config_reader.h"
#include <dlib/logger.h>

#include "NIST/Config.h"
#include "NIST/StdStringFcn.h"
//#include "NIST/CLogger.h"
#include "NIST/AgentCfg.h"
#include "NIST/Logger.h"


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


#include "ResourceIntegrator.h"
AgentConfigurationEx::AgentConfigurationEx() {}
CResourceHandler * AgentConfigurationEx::findResource(std::string id)
{
	for(int i=0; i< _resourceHandlers.size(); i++)
		if(_resourceHandlers[i]->_identifier == id)
			return _resourceHandlers[i];
		return NULL;
}

CCellHandler * AgentConfigurationEx::findCell(std::string id)
{
	for(int i=0; i< _cellHandlers.size(); i++)
		if(_cellHandlers[i]->_cell->identifier == bstr_t(id.c_str()))
			return _cellHandlers[i];
		return NULL;
}

CJobHandler * AgentConfigurationEx::findJob(std::string id)
{
	for(int i=0; i< _jobHandlers.size(); i++)
		if(_jobHandlers[i]->_job->identifier == bstr_t(id.c_str()))
			return _jobHandlers[i];
		return NULL;
}
CPartHandler * AgentConfigurationEx::findPart(std::string id)
{
	for(int i=0; i< _partHandlers.size(); i++)
		if(_partHandlers[i]->_part->identifier == bstr_t(id.c_str()))
			return _partHandlers[i];
		return NULL;
}
CProcessPlanHandler * AgentConfigurationEx::findProcessPlan(std::string id)
{
	for(int i=0; i< _processPlanHandlers.size(); i++)
		if(_processPlanHandlers[i]->_processplan->identifier == bstr_t(id.c_str()))
			return _processPlanHandlers[i];
		return NULL;
}

int AgentConfigurationEx::thread(int aArgc, const char *aArgv[])
{
	//sLogger << LENTRY  << "MTConnect Agent Service Started " << nowtimestamp() << "\n";

#ifdef OBSERVER
	// Test out observer functionality
	Device *dev = getDeviceByName(devicename);
	DataItem *di = dev->getDeviceDataItem("Xabs");
	di->addObserver(new  BusyObserver("Xabs", di));
#endif
	try{
		std::string cfgfile = ::ExeDirectory() + "VirtualFactoryTestbed.xml";


		if(GetFileAttributesA((::ExeDirectory() + INI_FILENAME).c_str())== INVALID_FILE_ATTRIBUTES)
			throw std::exception(("No " +::ExeDirectory() + INI_FILENAME + " file").c_str());
		config.load( ::ExeDirectory() + INI_FILENAME);
		_devicexmlpath =  config.GetSymbolValue("CONFIG.DevicesFolder", ::ExeDirectory()).c_str();
		_devicefile =  config.GetSymbolValue("CONFIG.DevicesFile", "Devices.xml").c_str();
		_cfgfile =  config.GetSymbolValue("CONFIG.CfgFile","Agent.cfg").c_str();
		_httpPort =  config.GetSymbolValue("CONFIG.HttpPort","80").toNumber<int>();
		_agentcfg.SetDevicesXmlFolder(_devicexmlpath);
		_agentcfg.SetHttpPort(_httpPort);
		_agentcfg.SetXmlFile(_devicefile);
		_agentcfg.SetCfgFile(_cfgfile);
		_agentcfg.SetDestinationFolder(::ExeDirectory());
		SetCurrentDirectory(::ExeDirectory().c_str()); // fixes Agent file lookup issue

		if( GetFileAttributesA(cfgfile.c_str())!= INVALID_FILE_ATTRIBUTES)
		{
			cmsd.ParseCMSD(cfgfile);
			for(int i=0 ; i< cmsd.resources.size(); i++)
			{
				Resource * r = (Resource *) cmsd.resources[i].get();
				std::string name = (LPCSTR) r->name;
				if(name.empty() || name == "None")  // something wrong
					continue; 

				_agentcfg.AddDevice(name,  // M1, M2
					"Command", // lookup name in devices.xml folder
					"127.0.0.1:81/"+name, 
					"0");			//writing to agent will be done using thread pointer not SHDR

				CResourceHandler *  _resourceHandler = new CResourceHandler((AgentConfigurationEx * ) this,r, &cmsd);
				_resourceHandlers.push_back(_resourceHandler);
				_resourceHandlers.back()->Configure( config,(LPCSTR) r->identifier,  name, "Command", "127.0.0.1:81/"+name,_devicexmlpath);

			}
			for(int i=0 ; i< cmsd.cells.size(); i++)
			{
				Cell * c = (Cell *) cmsd.cells[i].get();
				std::string name = (LPCSTR) c->name;
				CCellHandler *  _cellHandler = new CCellHandler((AgentConfigurationEx * ) this, c,&cmsd);
				_cellHandlers.push_back(_cellHandler);
				for(int j=0; j< c-> resourceIds.size(); j++)
				{
					CResourceHandler * r  =  findResource((LPCSTR) c-> resourceIds[j]) ;
					if(r!=NULL)
						_cellHandler->_resources.push_back(r);
				}
			}
		}

		GLogger.DebugString()=true;

		_agentcfg.Start(this);


		for(int i=0; i< _resourceHandlers.size(); i++)
			_group.create_thread(boost::bind(&CResourceHandler::Thread, _resourceHandlers[i]));

		for(int i=0 ; i< cmsd.jobs.size(); i++)
		{		
			CJobHandler *  _jobHandler = new CJobHandler((AgentConfigurationEx * ) this, (Job*) cmsd.jobs[i].get(),&cmsd,_cellHandlers);
			_jobHandlers.push_back(_jobHandler);
			_group.create_thread(boost::bind(&CJobHandler::Cycle, _jobHandler));
		}
#if 0
		_agentcfg.WriteCfgFile();
		//_agentcfg.Start();  // can just use the regular start of below, need to cofigure main?
		char *argv[4] = {
			"agent.exe",
			"debug",
			"" 
		};
		std::string file = _cfgfile; // change if not Agent.cfg
		argv[2]= new char[file.size() + 1]; 
		strcpy(argv[2], file.c_str()); 
		MTConnectService::main( 2,(const char **) argv);
#endif
	}
	catch(...) {}

	return 0;
}
// Start the server. This blocks until the server stops.
void AgentConfigurationEx::start()
{
	cond.notify_all();  
	AgentConfiguration::start();
}
void AgentConfigurationEx::stop()
{
	for(int i=0; i< _resourceHandlers.size(); i++)
		_resourceHandlers[i]->Stop();

	_group.join_all();
	AgentConfiguration::stop();
}
