//
// CmdHandler.cpp
//

// This software was developed by U.S. Government employees as part of
// their official duties and is not subject to copyright. No warranty implied 
// or intended.

#include "StdAfx.h"
#include "CmdHandler.h"
#include "agent.hpp"
#include "MTCAgentCmdEcho.h"

#include "NIST/Logger.h"
static void trans_func( unsigned int u, EXCEPTION_POINTERS* pExp )
{
	std::string errmsg =  StdStringFormat("COpcAdapter In trans_func - Code = 0x%x\n",  pExp->ExceptionRecord->ExceptionCode);
	OutputDebugString(errmsg.c_str() );
	throw std::exception(errmsg.c_str() , pExp->ExceptionRecord->ExceptionCode);
} 


CCmdHandler::CCmdHandler(AgentConfigurationEx * config)
{
	_agentconfig=config;
	_nSleep=1000;
}

CCmdHandler::~CCmdHandler(void)
{
}
void CCmdHandler::Configure(crp::Config	& config, 
					   std::string device, 
					   std::string xmldevice, 
					   std::string ipaddr,
					   std::string devicexmlpath)
{
	_config=config; 
	_device =device;
	_xmldevice =xmldevice; 
	_ipaddr= ipaddr;
	_devicexmlpath= devicexmlpath;
	std::string filename = RecursiveFileFind(devicexmlpath, xmldevice + ".txt");;
	_model= MTConnectDeviceParser().ReadDeviceDescription(filename);

}
void CCmdHandler::SetMTCTagValue(std::string device, std::string tag, std::string value)
{
	Agent * agent = _agentconfig->getAgent();
	Device *dev = agent->getDeviceByName(device);
	DataItem *di = dev->getDeviceDataItem(tag);
	if (di != NULL)
	{
		std::string time = getCurrentTime(GMT_UV_SEC);
		agent->addToBuffer(di, value, time);
	}
	//else
	//	sLogger << LINFO  <<  "(" << device << ") Could not find data item: " << tag << "\n";
}
void CCmdHandler::SetMTCConditionValue(std::string device, std::string tag, 
									   std::string alarmLevel,
									   std::string sNativeCode,
									   std::string alarmSeverity,
									   std::string sQualifier,
									   std::string sAlarmMessage)
{
	Agent * agent = _agentconfig->getAgent();
	Device *dev = agent->getDeviceByName(device);
	DataItem *di = dev->getDeviceDataItem(tag);
	//// Conditon data: LEVEL|NATIVE_CODE|NATIVE_SEVERITY|QUALIFIER
	std::string szCondValue =  alarmLevel + /*normal/alarm*/
		"|" + sNativeCode +
		"|" + alarmSeverity+
		"|" + sQualifier+
		"|" + sAlarmMessage;
	std::string time = getCurrentTime(GMT_UV_SEC);
	agent->addToBuffer(di, szCondValue, time);
}
void CCmdHandler::WaitWithPossibleFault()
{		
	static int waitFault=0;
	waitFault--;
	if(	waitFault<=0)
	{
		SetMTCConditionValue(_device, "system_cond", "FAULT", "0", "0","HIGH", "DAY TRIPPING");
		waitFault= (rand() % 25);
	}
	::Sleep(1000* (rand() % 10));
	SetMTCConditionValue(_device, "system_cond", "NORMAL", "0", "0","HIGH", "DAY TRIPPING");
}

void CCmdHandler::Cycle()
{
	GLogger << FATAL << "CCmdHandler::Cycle()" << std::endl; 
	std::vector<DataDictionary>  cycledatum ;
	boost::timer delaytimer;
	COleDateTime now;
	HRESULT hr;
	int minute;
	int nHeartbeat=0;
	_mRunning=true;
	int nLastCmdNum=-1;
	int nPartCount=0;

	hr = ::CoInitialize(NULL);
	_set_se_translator( trans_func );  // correct thread?

	//::Sleep(10000);
	boost::mutex::scoped_lock lock(_access);
	this->_agentconfig->cond.wait(lock);


	SetMTCTagValue(_device, "execution", "READY" );
	SetMTCTagValue(_device, "avail", "AVAILABLE" );
	SetMTCTagValue(_device, "controllermode", "AUTOMATIC" );
	SetMTCTagValue(_device, "power", "ON" );

	while(_mRunning)
	{
		try {
			SetMTCTagValue(_device, "heartbeat", StdStringFormat("%d",nHeartbeat++) );

			// Read Command Agent values
			cycledatum = _parser.ReadStream(_ipaddr);

			// Detect change event
			if(cycledatum.size() == 0)
			{
				::Sleep(10000);
				continue;
			}
			std::string command = cycledatum[0]["command"];
			int nCmdNum = ConvertString<int>(cycledatum[0]["cmdnum"],nLastCmdNum);

			//	SelectiveMerge(std::vector<std::string> itemlist, DataDictionary & itemstomerge)
			SetMTCTagValue(_device, "command_echo", cycledatum[0]["command"] );
			SetMTCTagValue(_device, "cmdnum_echo", cycledatum[0]["cmdnum"]);
			SetMTCTagValue(_device, "program", cycledatum[0]["program"]);
			SetMTCTagValue(_device, "partid", cycledatum[0]["partid"]);
			if(command=="RESET" && nLastCmdNum!=nCmdNum) //  execution== STOPPED
			{
				AtlTrace("Command = %s ComandNum %d:%d\n",command.c_str(), nCmdNum ,nLastCmdNum );
				SetMTCTagValue(_device, "execution", "READY" );
			}

			else if(command=="RUN" && nLastCmdNum!=nCmdNum)
			{
				AtlTrace("Command = %s ComandNum %d:%d\n",command.c_str(), nCmdNum ,nLastCmdNum );
				SetMTCTagValue(_device, "execution", "ACTIVE" );
				WaitWithPossibleFault(); // ::Sleep(1000* (rand() % 10));
				SetMTCTagValue(_device, "execution", "STOPPED" );
				SetMTCTagValue(_device, "PartCountAct", StdStringFormat("%d",nPartCount++)  );
				
			}
			::Sleep(_nSleep);
			nLastCmdNum=nCmdNum;
		}
		catch(std::exception e)
		{
			AtlTrace("%s%s", "CCmdHandler::Cycle() exception " , e.what());
		}
		catch(...)
		{
			AtlTrace("CCmdHandler::Cycle() exception ");
		}
	}
	::CoUninitialize();
}