//
// ResourceIntegrator.h
//

#pragma once
#include <string>
#include <vector>
#include <map>

#include <comdef.h>
#pragma comment( lib, "msxml2.lib" )
#import <msxml6.dll>



struct caseinsenstive_less
{
  bool operator() (const bstr_t & s1, const bstr_t & s2) const
  {
	return VarBstrCmp(const_cast<bstr_t&>( s1).GetBSTR() , const_cast<bstr_t&>( s2).GetBSTR(), LOCALE_USER_DEFAULT , NORM_IGNORECASE)  < 1;
  }
};

typedef std::map<bstr_t, bstr_t,caseinsenstive_less> MappedValues;

class Time
{
public:

	Time() { time="None"; }
	bstr_t time;
	bstr_t units;
};

class Distribution
{
public:
	Distribution() { name=L"None"; distreference=L"None";}
	static std::map<bstr_t, Distribution> distributions;
	bool IsEmpty() { return name == _bstr_t(L"None"); }
	bstr_t MapArenaDistribution() ;
	bstr_t name;
	bstr_t distname;
	bstr_t units;
	bstr_t distreference;
	MappedValues mappedvalues;
};


class Resource
{
public:
	Resource();
	bool IsEmpty() { return name == _bstr_t(L"None"); }
	bstr_t name;
	bstr_t identifier;

	bstr_t serial_number;
	bstr_t capacity;
	bstr_t manufacturer;
	Distribution mttr;
	Distribution mtbf;
	std::map<Distribution,Distribution> downtimes;
};

class Part
{
public:
	Part();
	bool IsEmpty() { return name == _bstr_t(L"None"); }
	bstr_t name;
	bstr_t identifier;
	bstr_t BOM;
	bstr_t processplanidentifier;

	Distribution arrivals;
};

class Process
{
public:
	Process() { identifier=L"None"; }
	bool IsEmpty() { return identifier == _bstr_t(L"None"); }
	bool IsSequence() { return steps.size() > 0; }

	bstr_t identifier;
	bstr_t repetitionCount;
	std::vector<bstr_t> resourcesRequired;
	Time setupTime;
	Time operationTime;
	bstr_t scrapPercentage;
	bstr_t partsProducedId;
	bstr_t partsProducedQuantity;
	bstr_t partsConsumedId;
	bstr_t  partsConsumedQuantity;
	bstr_t type;
	std::vector<bstr_t> steps;
};
class ProcessPlan
{
public:
	ProcessPlan() {  identifier=L"None"; }
	bool IsEmpty() { return identifier == _bstr_t(L"None"); }
	std::vector<bstr_t> partsProduced;
	std::vector<bstr_t> partsConsumed;
	bstr_t identifier;
	bstr_t firstProcessId;
	std::vector<Process> processes;
	Process FindProcess(bstr_t name);

};
class Cell
{
public:
	Cell() {  name=L"None"; }
	bool IsEmpty() { return name == _bstr_t(L"None"); }
	bstr_t name;
	bstr_t identifier;
	bstr_t units;
	std::vector<bstr_t> resourceIds;
};

class Job
{
public:
	Job() {  name=L"None"; }
	bool IsEmpty() { return name == _bstr_t(L"None"); }
	bstr_t name;
	std::vector<bstr_t> partIds;
	std::vector<bstr_t> partQuantity;
};

class CResourceIntegrator
{
public:
	CResourceIntegrator(void);
	~CResourceIntegrator(void);
	void ReadCmsdXmlFile(bstr_t);
	void ParseDataItems();
	Resource & FindResourceByName(bstr_t name);
	Resource & FindResourceById(bstr_t name);
	ProcessPlan & FindProcessPlanByPart(bstr_t name);
	Cell & FindCellById(bstr_t id);
	Part & FindPartById(bstr_t name);
	///////////////////
	bstr_t GetProperty(MSXML2::IXMLDOMNodePtr pNode,bstr_t PropName, bstr_t defaultVal, bstr_t NodeType=L".//Property");
	//Distribution GetStatisticalProperty(MSXML2::IXMLDOMNodePtr pNode,bstr_t PropName); // return none if doesnt exist
	MappedValues GetNameValueProperties(MSXML2::IXMLDOMNodePtr pNode, bstr_t NodeType=L".//Property");
	bstr_t GetElement(MSXML2::IXMLDOMNodePtr pNode,bstr_t ElementName, bstr_t defaultVal=L"None");
	Distribution GetDistribution(MSXML2::IXMLDOMNodePtr pNode);

	std::vector<Resource> resources;
	std::vector<Cell> cells;
	std::vector<Part> parts;
	std::vector<ProcessPlan> processplans;
	std::vector<Job> jobs;

	MSXML2::IXMLDOMDocument2Ptr        m_pXMLDoc;

};
