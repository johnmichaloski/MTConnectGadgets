//
// AgentThread.cpp
//

// This software was developed by U.S. Government employees as part of
// their official duties and is not subject to copyright. No warranty implied 
// or intended.
#include "StdAfx.h"
#include "Resource.h"
#include "AgentThread.h"
#include "ShdrCommandCellView.h"
#include "StdStringFcn.h"
#include "config.hpp"
#include "agent.hpp"

class AgentEx : public Agent
{
public:
	std::string contents; 
	AgentEx(CShdrCommandCellView * view) :_view(view)
	{
	}
	virtual std::string handleExtensionCall(const std::string& call, const std::string& device)
	{ 
		BOOL bHandled;
		::ReadFile( ::ExeDirectory() + "jsmtconnect.html", contents);
		return contents; 
	}
	CShdrCommandCellView * _view;
};

CAgentThread::CAgentThread(CShdrCommandCellView * view) : _view(view)
{
}

CAgentThread::~CAgentThread(void)
{
}

void CAgentThread::Run()
{
	char *argv[3] = {
		"agent.exe",
		"debug",
		"agent0.cfg"
	};
	SetCurrentDirectory(::ExeDirectory().c_str());
	AgentConfiguration config;
	config.mAgent = new AgentEx(_view);
	config.main(3, (const char **) argv);
}
