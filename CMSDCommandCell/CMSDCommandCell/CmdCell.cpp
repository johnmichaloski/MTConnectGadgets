//
// CmdCell.cpp
//
// This software was developed by U.S. Government employees as part of
// their official duties and is not subject to copyright. No warranty implied 
// or intended.

#include "StdAfx.h"
#include "CmdCell.h"

#include "NIST/Config.h"
#include "NIST/StdStringFcn.h"
//#include "NIST/CLogger.h"
#include "NIST/Logger.h"
#include "NIST/AgentCfg.h"
#include "MTCAgentCmd.h"
#include "MainFrm.h"
#include "HtmlTable.h"

#include "EquationSolver.h"
using namespace EquationHelper;
using std::size_t;
using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::ios;
typedef EquationSolver ES;

extern CLogger FurLogger;


int CJobCommands::MaxQueueSize=2;
extern CMainFrame * _wndMain;
static void trans_func( unsigned int u, EXCEPTION_POINTERS* pExp )
{
	std::string errmsg =  StdStringFormat("COpcAdapter In trans_func - Code = 0x%x\n",  pExp->ExceptionRecord->ExceptionCode);
	OutputDebugString(errmsg.c_str() );
	throw std::exception(errmsg.c_str() , pExp->ExceptionRecord->ExceptionCode);
} 

//////////////////////////////////////////////////////////////////////////////////////////////
std::string CJobCommand::ToString()
{
	std::stringstream str;
	str<<	"Parent         " << plan->_pParentPart->identifier << std::endl;
	str<<	"Current Step   " << plan->currentStep << std::endl;
	str<<	"Current JobId  " << plan->currentJobId << std::endl;
	str<<	"Active         " << plan->bActive << std::endl;
	//	for(int i=0; i < currentcell.size(); i++);
	for(int i=0; i < processes.size(); i++)
	{
		ProcessPlan * plan=	currentprocessplans.back();

		//for(int i=0;i< 	plan->steps.size(); i++)
		//{
		//	Process *process = plan->processes[i];
		str<<	"     ==================================" << std::endl;
		str<<	"     ProcessPlan      " << i <<  "  " <<  plan->identifier  << std::endl;
		str<<	"     Process         " << i <<  "  " <<  processes[i]->identifier  << std::endl;
		str<<	"     JobId           " << i <<  "  " <<  _jobId  << std::endl;
		str<<	"     PartID          " << i <<  "  " <<  _partid  << std::endl;
		str<<	"     Cell            " << i <<  "  " <<  processes[i]->resourcesRequired[0]  << std::endl;
		Cell * cell= _cmsd->FindCellById((LPCSTR)  processes[i]->resourcesRequired[0]);
		//str<<	"     Resource        " << i <<  "  " <<  currentcell[i]  << std::endl;
		if(cell!= NULL)
			str<<	"     Resource        " << i <<  "  " <<  cell->resourceIds[0] << std::endl;

		
	}
	return str.str();
}

int CJobCommand::IsDone() 
{ 
	if(plan ==NULL) 
	{
		OutputDebugString(StdStringFormat("CJobCommand::NextStep Error no process plan \n").c_str());
		DebugBreak();
		return -1;

	}		
	int step = plan->currentStep;
	return (step >= plan->steps.size()); 
}



Job *  CJobCommand::AddJob(AgentMgr * _agentconfig, CCMSDIntegrator * cmsd, int job, std::string partid)
{

	_partid=partid;
	_jobId = ConvertToString(job++);
	config=_agentconfig;
	_cmsd=cmsd;

	ajob= new Job();
	ajob->identifier = (LPCSTR)_jobId.c_str();
	ajob->partIds.push_back((LPCSTR) _partid.c_str());
	ajob->partQuantity.push_back("1");  // only ake 1 part at time for now
	//asset.jobs->push_back(IObjectPtr((IObject *) ajob));

	part = _cmsd->FindPartById( partid.c_str());
	if(part==NULL)
	{
		OutputDebugString(StdStringFormat("CJobCommand::AddPlan Error no part \n").c_str());
		DebugBreak();
		return ajob;
	}
	plan = new ProcessPlan();
	*plan = *_cmsd->FindProcessPlanById(part->processplanidentifier);
	/*if(*plan==NULL)
	{
	OutputDebugString(StdStringFormat("CJobCommand::AddPlan Error no part \n").c_str());
	DebugBreak();
	return;
	}*/

	plan->_pParentPart=part;
	plan->currentStep =0;
	plan->currentJobId =job;
	plan->jobId= (LPCSTR) _partid.c_str();
	plan->bActive=false;
	_currentstep=0;
	steps = plan->steps;;

	currentprocessplans.push_back(plan);

	//int step = plan->currentStep;

	sequence.clear(); oplist.clear();cells.clear(); operations.clear();
	for(int i=0;i< 	plan->steps.size(); i++)
	{
		Process *process = plan->processes[i];
		processes.push_back(process);
		bDone.push_back(false);
		
		// NOT WORKING
			//Process* process = plan->FindProcess(steps[step]);
		CCellHandler * nextcell = _agentconfig->findCell((LPCSTR) process->resourcesRequired[0]);
		currentcell.push_back(nextcell);


		std::string program= (LPCSTR)  plan->PartProgram(i); // or i+1 plan->currentStep);;
		currentprogram.push_back(program);

		if(i>0) sequence+=","; sequence+=StdStringFormat("%d", i*10); 
		if(i>0) oplist+=","; oplist+=plan->steps[i]; 
		if(i>0&& process!=NULL) cells+=","; cells+=process->resourcesRequired[0];
		if(i>0&& process!=NULL) operations+=","; operations+=(LPCSTR) process->description;

	}
	for(int i=0; i < processes.size(); i++)
	{
		_ProcessPlanId.push_back(  (LPCSTR) plan->identifier );
		
		Process * process =  plan->processes[i];
		_CellResourceRequired.push_back((LPCSTR)  process->resourcesRequired[0]);
		Cell * cell= _cmsd->FindCellById((LPCSTR)  process->resourcesRequired[0]);
		//str<<	"     Resource        " << i <<  "  " <<  currentcell[i]  << std::endl;
		if(cell!= NULL)
		{
			//_ResourceRequired.push_back((LPCSTR) cell->resourceIds[0]);
			Resource * r = cmsd->FindResourceById((LPCSTR) cell->resourceIds[0]);
			_ResourceRequired.push_back((LPCSTR) r->name);
		}


	}
	_currentstep=0;
	return ajob;
}
void CJobCommand::LoadResources(CResourceHandlers *resources)
{
	for(int i=0; i< _ResourceRequired.size();i++)
	{
		_ResourceHandlers.push_back(resources->Find(_ResourceRequired[i]));
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CJobCommands::CJobCommands(AgentMgr * _agentconfig, CCMSDIntegrator * _cmsd) 
{
	pi=0;
	agentconfig= _agentconfig;
	cmsd= _cmsd;
	_resourceHandlers=NULL;
}

CJobCommand *  CJobCommands::AddJob(AgentMgr * _agentconfig, CCMSDIntegrator * _cmsd, int jobId, std::string partid)
{
	if( this->size() >= MaxQueueSize)
		return NULL; 

	partids.push_back(partid);

	CJobCommand * job = new CJobCommand(this);
	job->AddJob(_agentconfig,_cmsd, jobId, partid);
	push_back(job);
	return job;
}


// This is the root of the jobs tree
void CJobCommands::InitJobs(Job *	job) 
{
	//jobids = job->partIds;
	for(int i=0 ; i< job->partIds.size(); i++)
	{
		parts.push_back( (LPCSTR) job->partIds[i]);
		numparts[ (LPCSTR) job->partIds[i]]= 0;
		finishedparts[ (LPCSTR) job->partIds[i]]=0;
		totnumparts[ (LPCSTR) job->partIds[i]]=ConvertString<int>((LPCSTR)job->partQuantity[i],1);
	}
	std::map<std::string, int> partcounts;
	for(int i=0 ; i< job->partIds.size(); i++)
	{
		partcounts[(LPCSTR) job->partIds[i]]=ConvertString<int>((LPCSTR) job->partQuantity[i],9);
	}
	for(std::map<std::string, int>::iterator it=partcounts.begin(); it!= partcounts.end(); it++)
	{		
		for(int i=0; i< (*it).second; i++)
			random_part.push_back((*it).first);
	}

	// Now randomize part making
	std::random_shuffle ( random_part.begin(), random_part.end() );

	// Get Properties that may change from job to job - These are GLOBALS
	// Get KWH Cost
	std::string kwh= job->GetPropertyValue("KWH"); // we will assume cost but should add description tag
	ControlThread::globalCosts["KWH"] = ConvertString<double>(kwh,0.0);   // no cost if not found :(
	GLogger << FATAL << ControlThread::globalCosts["KWH"] << std::endl;

}
//
void CJobCommands::IncPart(std::string partid)
{
	numparts[ partid]= numparts[ partid]+1;
	finishedparts[ partid]=finishedparts[ partid]+1;
}
int CJobCommands::PartsInProcess()
{
	int parts=0;
	for(std::map<std::string,int >::iterator it = finishedparts.begin(); it!=finishedparts.end(); it++)
		parts+=(*it).second;
	return parts;
}

int CJobCommands::AllFinished() 
{			
	for(std::map<std::string,int >::iterator it=finishedparts.begin(); it!=finishedparts.end(); it++)
	{
		if((*it).second < totnumparts[(*it).first])
			return false;
	}
	return true;
}
void  CJobCommands::Newworkorder()
{	
	while(IsNewWorkorder()) 
	{
		if(AllFinished())
			break;
		if(this->size() >0  )
		{
			CJobCommand * job = at(this->size()-1);
			if(job == NULL || job->_ResourceHandlers.size() <=0)
				break;

			CResourceHandler * resource = at(this->size()-1)->_ResourceHandlers[0];
			if(resource == NULL)
				break;
			if(resource->GetState() == "blocked")
			{
				::Sleep(1);
				break;  // No new jobs - already blocked...
			}
		}

		int current = ((int) (this->size()-1) >0) ? this->size()-1 : 0;
		std::string partid = GetPartId(current);
		CJobCommand * job = AddJob(agentconfig,cmsd, (int) (this->size() ),partid);  // error FIXME
		if(job==NULL)
			break;

		job->LoadResources(_resourceHandlers);

		//std::string d= back()->ToString();
		//OutputDebugString(d.c_str());

	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CResourceHandler::CResourceHandler(AgentConfiguration * agent, AgentMgr * config, Resource * r,  CCMSDIntegrator * cmsd) 
{
	_agent=agent;
	_agentconfig=config;
	_cmsd=cmsd;
	_resource=r;
//	_nCurrentStep=-1;
			job = NULL;
		currentJob=NULL; 

}

CResourceHandler::~CResourceHandler(void)
{
}
void CResourceHandler::Configure(crp::Config	& config, 
							std::string identifier, 
							std::string device, 
							std::string xmldevice, 
							std::string ipaddr,
							std::string devicexmlpath)
{
	_config=config; 
	_identifier=identifier;
	_device =device;
	_xmldevice =xmldevice; 
	_ipaddr= ipaddr;
	_devicexmlpath= devicexmlpath;
	std::string filename = RecursiveFileFind(devicexmlpath, xmldevice + ".txt");;
	_model= MTConnectDeviceParser().ReadDeviceDescription(filename);
		currentJob=NULL; 
//	_currentplan=NULL;

}
void CResourceHandler::SetMTCTagValue(std::string device, std::string tag, std::string value)
{
	Agent * agent = _agent->getAgent();
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

CResourceHandler::CResourceHandler(Resource * r, CCMSDIntegrator * cmsd)
{
	job=NULL;
	_cmsd=cmsd;
	_resource=r;
	currentJob=NULL; 

	std::string name = (LPCSTR) r->name;

	std::string mtbf= r->GetPropertyValue("Mtbf");
	std::string mttr= r->GetPropertyValue("Mttr");
	std::string mttp= r->GetPropertyValue("Mttp");

	std::string mtbfunits= r->GetPropertyUnits("Mtbf");
	std::string mttrunits= r->GetPropertyUnits("Mttr");
	std::string mttpunits= r->GetPropertyUnits("Mttp");

	std::string inqMax= r->GetPropertyValue("InQueue");
	std::string outqMax= r->GetPropertyValue("OutQueue");
	inqueue.nMaxSize= ConvertString<int>(inqMax,1); 
	outqueue.nMaxSize= ConvertString<int>(inqMax,1); 

	SetMTBF(ConvertString<double>(mtbf.c_str(), -1.0) * 60.0);// min to sec
	SetMTTR(ConvertString<double>(mttr.c_str(), -1.0) * 60.0);// min to sec
	SetMTTP(ConvertString<double>(mttp.c_str(), -1.0));// sec
	Setup();

	for(int i=0; i<  r->properties.size(); i++)
	{
		std::string name = r->GetPropertyName((LPCSTR) r->properties[i]);
		
		std::string sPropDesc= r->GetProperty(i, 3);  //r->GetPropertyDescription(name);
		if(Trim(sPropDesc) == "COST")
		{
			// Error - can have multiple costs and properties with same name
			std::string sPropUnit= r->GetProperty(i, 2); //GetPropertyUnits(name);
			std::string sPropValue= r->GetProperty(i, 1);   // GetPropertyValue(name);
			std::string  sCostFactor= sPropUnit.substr(0,sPropUnit.find(":"));
			std::string  sCostState = sPropUnit.substr(sPropUnit.find(":")+1);

			std::string solvedvalue=ES::solve(sPropValue, 4);
			double value = ConvertString<double>(solvedvalue,0.0);
			// skip costs < 0
			if(value < 0.0)
				continue;
			AddCostFunction(CostFcnTuple(sCostState, name,sCostFactor, sPropDesc, 0.0, value));

			//OutputDebugString(StdStringFormat("Property Name = %s\n", name.c_str()).c_str());
		}
	}


	Trigger("init");
	Trigger("run");
}

static std::string GetTimeEstimate(std::string etime)
{
	if(etime.find("TRIA") != std::string::npos)
	{
		std::vector<std::string> decimals = TrimmedTokenize(etime, ",");
		int sec = ConvertString<int>(decimals[decimals.size()-1],0) * 60;
		if( decimals.size() > 0) 
			return HrMinSecFormat(sec);
	}
	return "00:00:00";

}

void CJobCommands::Update(CResourceHandlers * resourceHandlers)
{
	for(int i=0; i < size() ; i++)
	{
		int _current = at(i)->_currentstep;
		// only check this - if done
		// check next - if done and free - else nothing...
		if(_current>= at(i)->MaxStep())
		{
			IncPart(at(i)->CurrentPartId());
			// Done with job
			// for now erase
			this->erase(begin() + i);
			partids.erase(partids.begin() + i);
			continue;
		}
		
		CResourceHandler *  resource = resourceHandlers->FindResourceHandler(_current) ; //FindResourceHandler(_resourceHandlers,_current, at(i)->_ResourceRequired[_current]);
		if(resource == NULL) 
			continue;

		if(resource->outqueue.CanPop())
		{
			resource->outqueue.Pop();
			 at(i)->_currentstep++;
		}

		// revise current step in part from job
		_current = at(i)->_currentstep;
		if(_current>= at(i)->MaxStep())
			continue;	

		resource = resourceHandlers->FindResourceHandler(_current) ; 
		
		// Should push the next time...
		if(resource &&	resource->inqueue.CanPush())
		{
			if(_current< 0 || _current>= at(i)->MaxStep()) 
			{
				DebugBreak();
			}
			resource->inqueue.Push(at(i));
		}
	}
}


void CJobCommands::Run(CJobCommands * jobs, CResourceHandlers *  resourceHandlers)
{
	MaxQueueSize=2;
	m_Thread = boost::thread(&CJobCommands::process, this, jobs, resourceHandlers );
	m_bRunning=true;

}

void CJobCommands::process(CJobCommands * jobs, CResourceHandlers *  resourceHandlers)
{
	int nRefresh=100;

	_dUpdateRateSec=0.0;
	double _dSpeedupRateSec=0.0;
	double dUpdateWait=1.0;
	_resourceHandlers=resourceHandlers;
	while(_resourceHandlers==NULL) ::Sleep(100);
	while(m_bRunning)
	{
		ControlThread::RestartTimer();
		Newworkorder();               // done with job - start new work order
		Update(resourceHandlers);  // update queues to resource
		resourceHandlers->UpdateResourceHandlers();  // update state machine

		//if(AllFinished())
		//	break;
		if((nRefresh--)<0)
		{
			::PostMessage(_wndMain->m_hWnd, WM_COMMAND, DISPLAY_MSG,0);
			nRefresh=1000;
		}

		CResourceHandler * resourceHandler= _resourceHandlers->Find("LINE1_PS_CAST1_FUR1");
		if(resourceHandler!=NULL)
		{
			std::string dump;		
			//dump+ resourceHandler-> ToString();
			dump+= resourceHandler-> GenerateReport();
			FurLogger.LogMessage(StdStringFormat("Resource(%s) Report=%s\n",resourceHandler->_identifier.c_str(), dump.c_str() ) );;
		}
		dUpdateWait=1000.0;

		//OutputDebugString(StdStringFormat("END UpdateWait=%f\n",dUpdateWait ).c_str())  ;
		for(std::map<std::string, int > ::iterator it = finishedparts.begin() ; it!=finishedparts.end(); it++)
			OutputDebugString(StdStringFormat("END Total Number Parts %s =%d\n", ((*it).first).c_str(), finishedparts[(*it).first] ).c_str())  ;

		_dUpdateRateSec+= 1.0 * ControlThread::_dSpeedup; // one seconds times speed up

		::Sleep(1);
		// Break when shift time exceeded
		if( (_dUpdateRateSec ) > 3000.0)
			break;

	}

	for(int i=0 ; i<_resourceHandlers->size(); i++)
	{
		std::string tmp = _resourceHandlers->at(i)->GenerateReport();
		OutputDebugString(StdStringFormat("Resource(%s) Report=%s\n",_resourceHandlers->at(i)->_identifier.c_str(), tmp.c_str() ).c_str())  ;
	}
	
	std::map<std::string,double> states;
	for(int i=0;i<_resourceHandlers->size() ; i++)
		_resourceHandlers->at(i)->GenerateStateReport(states );



	CHtmlTable htmlTable; 
	std::string html = CHtmlTable::CreateHtmlSytlesheetFrontEnd("Precision Sand Casting Saginaw MI");;
	//html += htmlTable.HtmlGoogleChart(states);
	html += htmlTable.HtmlRaphaeleChart( );

	//html+= htmlTable.HtmlRaphaeleChartData(states );


	html += "</HEAD>\n";

	//std::string html = CHtmlTable()::CreateHtmlDocument();
	std::string header = "Machine," + _resourceHandlers->at(0)->GenerateCSVHeader("Minutes") + ",Utility<BR>Costs</BR>,Description";
	std::string alignment = ",right,right,right,right,right,right,right,";
	htmlTable.SetAlignment(alignment);
	htmlTable.SetHeaderColumns( header);

	for(int i=0;i<_resourceHandlers->size() ; i++)
	{
		std::string html1=_resourceHandlers->at(i)->Name() + ",";
		html1+= _resourceHandlers->at(i)->GenerateCSVTiming(60.00) + "," ;
		html1+= _resourceHandlers->at(i)->GenerateTotalCosts("","");
		html1+=  (LPCSTR) _resourceHandlers->at(i)->_resource->description;
		htmlTable.AddRow(header, html1);
	}


	CHtmlTable htmlRawTable; 
	std::string headerRaw = "Machine,Blocked,Starved,Down,Production,Off";
	htmlRawTable.SetHeaderColumns( headerRaw);
	std::map<std::string,double> rawstates;
	for(int i=0;i<_resourceHandlers->size() ; i++)
	{
		std::string html3;
		_resourceHandlers->at(i)->GenerateStateReport(rawstates,1.0 );
		html3+=_resourceHandlers->at(i)->Name() + ",";
		html3+=StdStringFormat("%8.4f,%8.4f,%8.4f,%8.4f,%8.4f\n",
			rawstates["blocked"],rawstates["starved"],rawstates["down"],rawstates["production"],rawstates["off"]);
		htmlRawTable.AddRows(headerRaw, html3);
	}


	CHtmlTable kpiTable; 
	std::string kpiheader = "Machine,MTBF,MTTR,INQ, OUTQ";
	kpiTable.SetHeaderColumns( kpiheader);
	for(int i=0;i<_resourceHandlers->size() ; i++)
	{
		std::string machine=_resourceHandlers->at(i)->Name() + ",";
		machine+= StdStringFormat("%8.4f,",_resourceHandlers->at(i)->MTBF  );
		machine+= StdStringFormat("%8.4f,",_resourceHandlers->at(i)->MTTR  );
		machine+= StdStringFormat("%d,",_resourceHandlers->at(i)->inqueue.nMaxSize  );
		machine+= StdStringFormat("%d",_resourceHandlers->at(i)->outqueue.nMaxSize  );
		kpiTable.AddRows(kpiheader, machine);
	}

	CHtmlTable htmlTable2; 
	std::string header2 = "Machine,Units,Name,State,Time,Cost";
	htmlTable2.SetHeaderColumns( header2);
	for(int i=0;i<_resourceHandlers->size() ; i++)
	{
		std::string machine=_resourceHandlers->at(i)->Name() + ",";
		std::string html2= _resourceHandlers->at(i)->GenerateCosts(machine,"\n") ;
		htmlTable2.AddRows(header2, html2);
	}


	html+=	"<h1>Precision Casting</h1>\n";
	for(int i=0; i < jobs->at(0)->_cmsd->documentation->size(); i++)
		html+= "<p> " + UrlDecode (   (LPCSTR) ((Documentation *) jobs->at(0)->_cmsd->documentation->at(i).get())->description);
	html+=	"<p>\n";

	html += htmlRawTable.CreateHtmlTable();
	html+=	"<p>\n";
	html += kpiTable.CreateHtmlTable();


	html+=	"<h2>Casting Line 1 Performance</h2>\n";

	for( std::map<std::string, int >::iterator it = finishedparts.begin(); it!= finishedparts.end(); it++)
		html+=StdStringFormat("<BR> Part %s Number Made = %d\n" , (*it).first.c_str(), (*it).second).c_str();
	html+=	StdStringFormat("<br>Time elapsed %8.4f in hours\n", _dUpdateRateSec/3600.0);
	html+=	StdStringFormat("<br>Time elapsed %8.4f in minutes\n", _dUpdateRateSec/60.0);
	html+=	StdStringFormat("<br>Time elapsed %8.4f in seconds\n", _dUpdateRateSec);
	
	html += htmlTable.CreateHtmlTable();
	html+="<br>";
	html+=	"<h1>Casting Line 1 Utility Costs By Item</h1>\n";
	html += CHtmlTable::HtmlStateInfo();
	html+="<br>";
	html += htmlTable2.CreateHtmlTable();

	html+="<div id=\"holder\";\"></div>\n";
	//html +=" var chart = new google.visualization.PieChart(document.getElementById('chart_div'));\n";
	//html +=" chart.draw(data, options);\n";

		//////////////////////////////////////////////////////////////////////////
	// Make table of pie charts of performance states
	HtmlTableMaker Table(3);
	for(int i=0;i<_resourceHandlers->size() ; i++)
	{
		std::string machine=_resourceHandlers->at(i)->Name() + ",";
		std::map<std::string,double> states;
		 _resourceHandlers->at(i)->GenerateStateReport(states,1000.0 );;
		Table.AppendTableCell(Raphael::InlinePieChart(states, machine + " State Use"));
	}
	html+=Table.MakeTable();

	html+= "</BODY>\n</HTML>\n";

	WriteFile(::ExeDirectory() + "Doc.html", html);
}