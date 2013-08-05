//
// MTCAgentCmdEcho.h : Defines the entry point for the console application.
//

// This software was developed by U.S. Government employees as part of
// their official duties and is not subject to copyright. No warranty implied 
// or intended.

#include <vector>
#include <string>
#include <boost\thread.hpp>

#include "config.hpp"
#include "NIST/Config.h"
#include "NIST/Logger.h"
#include "NIST/AgentCfg.h"

#include "CmdHandler.h"

class AgentConfigurationEx : public AgentConfiguration
{
	crp::Config										config;
	std::vector<std::string>						_devices, ipaddrs, _xmldevices;
	std::string										_devicexmlpath;
	boost::thread_group								_group;
	std::vector<CCmdHandler * >						 _cmdHandlers;
	CAgentCfg										_agentcfg;
	std::string										_devicefile ;
	std::string										_cfgfile ;
	int												_httpPort;
	// Configuruation file hack 
	std::string										file;
public:
	AgentConfigurationEx(){} 
	virtual int thread(int aArgc, const char *aArgv[]);
	virtual void start();
	virtual void stop();
	virtual void initialize(int aArgc, const char *aArgv[]);
	boost::condition_variable cond;


};