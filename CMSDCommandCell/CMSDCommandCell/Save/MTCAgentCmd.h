//
// MTCAgentCmd.h
//
// This software was developed by U.S. Government employees as part of
// their official duties and is not subject to copyright. No warranty implied 
// or intended.
#pragma once
#include <vector>
#include <string>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>
#include <boost/timer.hpp>
// MTConnect Agent code
#include "agent.hpp"
#include "config.hpp"




#include "config.hpp"

#include "NIST/config.h"
#include "NIST/AgentCfg.h"
#include "NIST/MTConnectStreamsParser.h"
#include "NIST/MTConnectDeviceParser.h"
#include "NIST/RunProcess.h"

#include "CmdCell.h"
#include <boost\thread.hpp>


class AgentMgr //: public AgentConfiguration
{
public:
	AgentConfiguration *							_agent;

	boost::thread_group								*_group;
	boost::condition_variable						cond;		// synchronize threads starting
	
	// application configuratio
	crp::Config										config;
	std::string										_devicexmlpath;
	std::string										_devicefile ;
	std::string										_cfgfile ;
	int												_httpPort;
	int												_nSpinup;
	static int										_debugSimulation;
	// Spawn device status agent
	CAgentCfg										_devicesAgentCfg;
	CFactorySpinUp									spinup;

	// CMSD command agent information
	CCMSDIntegrator									cmsd;
	CAgentCfg										_cmdAgentCfg;
	CResourceHandlers								_resourceHandlers;
	std::vector<CCellHandler * >					_cellHandlers;
//	std::vector<CJobHandler * >						_jobHandlers;
//	std::vector<CPartHandler * >					_partHandlers;
//	std::vector<CProcessPlanHandler * >				_processPlanHandlers;
	


public:
	AgentMgr();
	virtual int thread(int aArgc, const char *aArgv[]);
	virtual void start();
	virtual void stop();
	void clear();

	CResourceHandler * findResource(std::string name);
	CCellHandler * findCell(std::string id);
	//CJobHandler * findJob(std::string id);
	//CPartHandler * findPart(std::string id);
	//CProcessPlanHandler * findProcessPlan(std::string id);
};
