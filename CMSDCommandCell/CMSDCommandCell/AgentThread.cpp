//
// AgentThread.cpp
//

// This software was developed by U.S. Government employees as part of
// their official duties and is not subject to copyright. No warranty implied 
// or intended.
#include "StdAfx.h"
#include "Resource.h"
#include "AgentThread.h"
#include "CMSDCommandCellView.h"
#include "StdStringFcn.h"
#include "config.hpp"
#include "agent.hpp"

//class AgentEx : public Agent
//{
//public:
//	AgentEx(CCMSDCommandCellView * view) :_view(view){}
//	//virtual std::string handleExtensionCall(const std::string& call, const std::string& device)
//	//{ 
//	//	BOOL bHandled;
//	//		_view->OnBnClickedButton1(NULL, NULL, NULL, bHandled);
//	//	return ""; 
//	//}
//	CCMSDCommandCellView * _view;
//};

CAgentThread::CAgentThread(CCMSDCommandCellView * view) : _view(view)
{
}

CAgentThread::~CAgentThread(void)
{
}

void CAgentThread::Run()
{
	char *argv[2] = {
		"agent.exe",
		"debug"
	};
	SetCurrentDirectory(::ExeDirectory().c_str());
	AgentConfiguration config;
	//config.mAgent = new AgentEx(_view);
	config.main(2, (const char **) argv);
}
