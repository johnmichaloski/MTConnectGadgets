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

//#include "CmdCell.h"
#include <boost\thread.hpp>


class AgentConfigurationEx : public AgentConfiguration
{
public:
	crp::Config										config;
	//std::vector<std::string>						_devices, ipaddrs, _xmldevices;
	std::string										_devicexmlpath;
	boost::thread_group								_group;
	std::vector<CResourceHandler * >				_resourceHandlers;
	std::vector<CCellHandler * >					_cellHandlers;
	std::vector<CJobHandler * >						_jobHandlers;
	std::vector<CPartHandler * >					_partHandlers;
	std::vector<CProcessPlanHandler * >				_processPlanHandlers;
			CCMSDIntegrator cmsd;

	CResourceHandler * findResource(std::string name);
	CCellHandler * findCell(std::string id);
	CJobHandler * findJob(std::string id);
	CPartHandler * findPart(std::string id);
	CProcessPlanHandler * findProcessPlan(std::string id);

	CAgentCfg										_agentcfg;
	std::string										_devicefile ;
	std::string										_cfgfile ;
	int												_httpPort;

public:
	AgentConfigurationEx();
	virtual int thread(int aArgc, const char *aArgv[]);
	virtual void start();
	virtual void stop();
	boost::condition_variable cond;
};
