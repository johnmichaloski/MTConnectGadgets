//
// CmdHandler.h
//

// This software was developed by U.S. Government employees as part of
// their official duties and is not subject to copyright. No warranty implied 
// or intended.

#pragma once
#include <boost/timer.hpp>
#include <boost/thread/mutex.hpp>

#include "config.hpp"
#include "NIST/config.h"
#include "MTConnectStreamsParser.h"
#include "MTConnectDeviceParser.h"
class AgentConfigurationEx;

class CCmdHandler
{
public:
	CCmdHandler(AgentConfigurationEx * config);
	~CCmdHandler(void);
	void Configure(crp::Config	& config, 
		std::string device, 
		std::string xmldevice, 
		std::string ipaddr,
		std::string devicexmlpath);
	void Stop(){ _mRunning=false; }
	void Cycle();
	void SetMTCTagValue(std::string device, std::string tag, std::string value);
	void SetMTCConditionValue(std::string device, 
		std::string tag, 
		std::string alarmLevel="Normal",
		std::string sNativeCode="",
		std::string alarmSeverity="",
		std::string sQualifier="",
		std::string sAlarmMessage="");
	void WaitWithPossibleFault();

	AgentConfigurationEx *				_agentconfig;
	MTConnectStreamsParser				_parser;
	crp::Config							_config;
	std::string							_device, _xmldevice, _ipaddr,_devicexmlpath;
	bool								_mRunning;
	MTConnectDataModel					_model;
	boost::mutex _access;
	long								_nSleep;
};
