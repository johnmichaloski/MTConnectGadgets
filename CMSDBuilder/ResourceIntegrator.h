//
// ResourceIntegrator.h
//

#pragma once
#include <string>
#include <vector>
#include <map>
#include <comdef.h>
//#import <msxml6.dll>
#include "CMSD/CMSD.h"
#include "SimpleReflection.h"
#include <boost/shared_ptr.hpp>
#include "StdStringFcn.h"


#define ASSIGN(X,Y,Z) try { X=Y; } catch(...) { X=Z;};
#define CREATEIF(X,Y) try { if(Y != bstr_t(L"None") && Y != bstr_t(L"") ) X=std::string((LPCSTR)Y); } catch(...) { };
#define CREATEIFBSTR(X,Y) try { if(Y != bstr_t(L"None") && Y != bstr_t(L"")) X=Y; } catch(...) { };


class MyStructMeta;
class PropertyElement ;
struct DistributionReferenceProperty;
struct Shift;
struct Calendar;
struct Schedule;
struct Distribution;
struct Resource;
struct Cell;
struct Layout;
struct Part;
struct Process;
struct ProcessPlan;
struct Job;
#if 0
typedef boost::shared_ptr<PropertyElement> PropertyElementPtr;
typedef boost::shared_ptr<DistributionReferenceProperty> DistributionReferencePropertyPtr;
typedef boost::shared_ptr<Shift> ShiftPtr;
typedef boost::shared_ptr<Calendar> CalendarPtr;
typedef boost::shared_ptr<Schedule> SchedulePtr;
typedef boost::shared_ptr<Distribution> DistributionPtr;
typedef boost::shared_ptr<Resource> ResourcePtr;
typedef boost::shared_ptr<Cell> CellPtr;
typedef boost::shared_ptr<Layout> LayoutPtr;
typedef boost::shared_ptr<Part> PartPtr;
typedef boost::shared_ptr<Process> ProcessPtr;
typedef boost::shared_ptr<ProcessPlan> ProcessPlanPtr;
typedef boost::shared_ptr<Job> JobPtr;
#endif
typedef PropertyElement* PropertyElementPtr;
typedef DistributionReferenceProperty* DistributionReferencePropertyPtr;
typedef Shift* ShiftPtr;
typedef Calendar* CalendarPtr;
typedef Schedule* SchedulePtr;
typedef Distribution* DistributionPtr;
typedef Resource* ResourcePtr;
typedef Cell* CellPtr;
typedef Layout* LayoutPtr;
typedef Part* PartPtr;
typedef Process* ProcessPtr;
typedef ProcessPlan* ProcessPlanPtr;
typedef Job* JobPtr;


inline bool DataExists(bstr_t data) { return (data != bstr_t(L"None")); }
struct caseinsenstive_less
{
	bool operator() (const bstr_t & s1, const bstr_t & s2) const
	{
		return VarBstrCmp(const_cast<bstr_t&>( s1).GetBSTR() , const_cast<bstr_t&>( s2).GetBSTR(), LOCALE_USER_DEFAULT , NORM_IGNORECASE)  < 1;
	}
};

typedef std::map<bstr_t, bstr_t,caseinsenstive_less> MappedValues;

	// <Property><Name>SerialNumber</Name><Value>111-222-556677-6</Value></Property>
			//	<Property>
			//	<Name>arrivals</Name>
			//	<Description>interarrival time for parts of this type at machine 1</Description>
			//	<DistributionDefinitionReference>
			//		<DistributionDefinitionIdentifier>dddd:111</DistributionDefinitionIdentifier>
			//	</DistributionDefinitionReference>
			//</Property>

class PropertyElement //: public IObject
{
public:
	PropertyElement(bstr_t _name=L"None", bstr_t _value=L"None");
	void Load(MSXML2::IXMLDOMNodePtr  ini);
	void Save(CMSD::CProperty & prop);
	static bool IsPropertyElement(MSXML2::IXMLDOMNodePtr  ini);
	static bool PropertyElement::IsDistributionReferenceProperty(MSXML2::IXMLDOMNodePtr  pNode);
	static bool GetPropertyValue(MSXML2::IXMLDOMNodePtr  ini, bstr_t &name,   bstr_t &value);
	bstr_t identifier; // for identification purposes only - not part of CMSD XML
	bstr_t type;
	bstr_t name;
	bstr_t value;
	bstr_t units;
	bstr_t description;
	static std::vector<bstr_t>& GetTypeList();
	//BEGIN_METADATA(PropertyElement)
	//	STDFLD(identifier, type_is_bstr_t),
	//	STDFLD(name, type_is_bstr_t),
	//	STDFLD(value, type_is_bstr_t),
	//	STDFLD(description, type_is_bstr_t),
	//	END_METADATA

	template<typename T>
	void SaveProperties(T &_parent, std::vector<bstr_t> &properties)
	{
		for(int i=0; i< properties.size(); i++)
		{		
			std::vector<std::string> tokens = Tokenize(RightTrim(std::string((LPCSTR) properties[i]),";"),",");
			bstr_t name(L"None"),value(L"None"),units(L"None"),description(L"None");
			if(tokens.size() > 0) name=tokens[0].c_str();
			if(tokens.size() > 1) value=tokens[1].c_str();
			if(tokens.size() > 2) units=tokens[2].c_str();
			if(tokens.size() > 3) description=tokens[3].c_str();

			CMSD::CProperty prop = _parent.Property.append();
			std::vector<bstr_t>::iterator it =  std::find(GetTypeList().begin(), GetTypeList().end(), bstr_t(tokens[0].c_str()));
			if(it !=  GetTypeList().end())
			{	
				CREATEIF(prop.Unit.append() ,  units);
				CREATEIF(prop.Description.append() ,  description);
				if((*it) == bstr_t("Distribution"))
				{

				}
				else	if((*it) != bstr_t("Name"))
				{
					MSXML2::IXMLDOMElementPtr elem;
					MSXML2::IXMLDOMNodePtr node;
					elem = prop.GetNode()->ownerDocument->createElement(*it);
					node= prop.GetNode()->appendChild(elem);

					std::string id((LPCSTR) (*it));
					id=ReplaceOnce(id,"Reference", "Identifier");
					elem = prop.GetNode()->ownerDocument->createElement(bstr_t(id.c_str()));
					node->appendChild(elem);
				}
			}
			else
			{
				CREATEIF(prop.Unit.append() ,  units);
				CREATEIF(prop.Description.append() ,  description);
				prop.Name.append() = tokens[0].c_str();
				prop.Value2.append() = tokens[1].c_str();
			}
		}
	}

	template<typename T>
	void LoadProperties(T &_parent, std::vector<bstr_t> &properties)
	{
		bstr_t name, value, units, description;

		for(int i=0; i < _parent.Property.count();i++)
		{
			CMSD::CProperty prop =  _parent.Property[i];

			MSXML2::IXMLDOMNodeListPtr nodes = prop.GetNode()->childNodes;
			for(int j=0;  j< nodes->length; j++)
			{
				bstr_t elem = nodes->Getitem(j)->nodeName;
				std::vector<bstr_t>::iterator it =  std::find(GetTypeList().begin(), GetTypeList().end(), elem);
				if(it !=  GetTypeList().end())
				{	
					ASSIGN(units, ((std::string)prop.Unit[0]).c_str(), L"None"); 
					ASSIGN(description, ((std::string)prop.Description[0]).c_str(), L"None"); 
					if((*it)==bstr_t("Name")) 
					{  
						ASSIGN(name, ((std::string)prop.Name[0]).c_str(), L"None"); 
						ASSIGN(value, ((std::string)prop.Value2[0]).c_str(), L"None");

					}
					else if((*it)==bstr_t("Distribution")) 
					{
						// handled differently ... 
					}
					else 
					{ 
						name = (*it); 
						std::string id((LPCSTR) (*it));
						id=ReplaceOnce(id,"Reference", "Identifier");
						bstr_t valuestr = "./" + (*it) +"/" + id.c_str();
						MSXML2::IXMLDOMNodePtr node =  prop.GetNode()->selectSingleNode(valuestr);
						if(node!=NULL)
							value = node->text;
					}

					properties.push_back( name+ "," + value + "," + units   + "," + description + ";" );
				}
			}
		}
	}
};


struct Time
{
	Time() {time="None";  units=""; }
	bstr_t time;
	bstr_t units;
};
struct TimePeriod
{
	TimePeriod() { starttime="None";units=duration=""; }
	bstr_t starttime;
	bstr_t units;
	bstr_t duration;
};
struct Shift : public IObject
{
	Shift();
	void Load(MSXML2::IXMLDOMNodePtr  ini);
	void Save(CMSD::CShift &shift);
	bstr_t identifier;
	bstr_t description;

	bstr_t startTime;
	bstr_t duration;
	bstr_t applicableDay;
	std::vector<TimePeriod> breaks;

	BEGIN_METADATA(Shift)
		STDFLD(identifier, type_is_bstr_t),
		STDFLD(startTime, type_is_bstr_t),
		STDFLD(duration, type_is_bstr_t),
		STDFLD(applicableDay, type_is_bstr_t),
		STDFLD(properties, type_is_propertylist),
		STDFLD(description, type_is_bstr_t),
		END_METADATA
};

struct Calendar : public IObject
{
	Calendar();
	void Load(MSXML2::IXMLDOMNodePtr  ini);
	void Save(CMSD::CCalendar &cal);
	int ShiftsPerWeek();
	double HoursPerWeek();

	bstr_t identifier;
	bstr_t startdate;
	bstr_t enddate;
	bstr_t description;
	std::vector<Shift*> shifts;
	std::vector<std::string> shiftIds; // ids to shifts

	BEGIN_METADATA(Calendar)
		STDFLD(identifier, type_is_bstr_t),
		STDFLD(shiftIds, type_is_array),
		STDFLD(startdate, type_is_bstr_t),
		STDFLD(enddate, type_is_bstr_t),
		STDFLD(properties, type_is_propertylist),
		STDFLD(description, type_is_bstr_t),
		END_METADATA
};

struct Schedule : public IObject
{
	Schedule();
	void Load(MSXML2::IXMLDOMNodePtr  ini);
	void Save(CMSD::CSchedule &dist);
	bstr_t identifier;
	bstr_t description;
// stubbed out
	BEGIN_METADATA(Schedule)
		STDFLD(identifier, type_is_bstr_t),
		STDFLD(description, type_is_bstr_t),
		STDFLD(properties, type_is_propertylist),
		END_METADATA
};

struct Distribution : public IObject
{
	Distribution();
	void LoadProperty(MSXML2::IXMLDOMNodePtr  ini);  // property wrapper
	void LoadDefinition(MSXML2::IXMLDOMNodePtr  ini); // distributiondefinition wrapper
	void LoadDistribution(CMSD::CDistribution &distribution); // actual distribution parameters
	void Save(CMSD::CDistributionDefinition &dist);
	void Save(CMSD::CProperty &prop);
	void SaveDistribution(CMSD::CDistribution &dist);

	static std::map<bstr_t, Distribution> distributions;
	bool IsEmpty() { return name == _bstr_t(L"None"); }
	bstr_t MapArenaDistribution() ;
	///////////////////////////////////////////////////
	// type DistributionDefinition or Property
	enum DistType { Property, DistributionDefinition};
	bstr_t identifier;
	bstr_t name;
	bstr_t description;
	bstr_t units;
	bstr_t type;

	// Property
	bstr_t distname; 
	bstr_t distdescription;
	bstr_t distreference;
	MappedValues mappedvalues;
	bstr_t name1;
	bstr_t value1;
	bstr_t name2;
	bstr_t value2;
	bstr_t name3;
	bstr_t value3;

	///////////////////////////////////////////////////
	BEGIN_METADATA(Distribution)
		STDFLD(identifier, type_is_bstr_t),
		STDFLD(name, type_is_bstr_t),
		STDFLD(distname, type_is_bstr_t),
		STDFLD( units, type_is_bstr_t),
		STDFLD( name1, type_is_bstr_t),
		STDFLD( value1, type_is_bstr_t),
		STDFLD( name2, type_is_bstr_t),
		STDFLD( value2, type_is_bstr_t),
		STDFLD( name3, type_is_bstr_t),
		STDFLD( value3, type_is_bstr_t),
		END_METADATA
};

struct Resource : public IObject
{
	Resource();
	void Load(MSXML2::IXMLDOMNodePtr  ini);
	void Save(CMSD::CResource& resource);
	bool IsEmpty() { return name == _bstr_t(L"None"); }
	bstr_t name;
	bstr_t identifier;
	bstr_t type;
	bstr_t description;
	bstr_t hourlyRate;
	bstr_t hourlyRateUnit;

	// Properties
//	bstr_t serial_number;
//	bstr_t capacity;
//	bstr_t manufacturer;
	bstr_t model;
	bstr_t mtbfid;
	bstr_t mttrid;
	Distribution *mttr;
	Distribution *mtbf;

	std::map<Distribution,Distribution> downtimes;
	//std::vector<PropertyElement> simpleproperties;

	BEGIN_METADATA(Resource)
		STDFLD(identifier, type_is_bstr_t),
		STDFLD(type, type_is_bstr_t),
//		STDFLD(capacity, type_is_bstr_t),
		STDFLD(mtbfid, type_is_bstr_t),
		STDFLD(mttrid, type_is_bstr_t),
		STDFLD(hourlyRate, type_is_bstr_t),
		STDFLD(hourlyRateUnit, type_is_bstr_t),
//		STDFLD(manufacturer, type_is_bstr_t),
//		STDFLD(model, type_is_bstr_t),
		STDFLD(properties, type_is_propertylist),
		STDFLD(description, type_is_bstr_t),
		END_METADATA;

};

struct Cell : public IObject
{
	Cell();
	void Load(MSXML2::IXMLDOMNodePtr  ini);
	void Save(CMSD::CResource &resource);
	bool IsEmpty() { return name == _bstr_t(L"None"); }
	static bool IsResourceCell(MSXML2::IXMLDOMNodePtr in);

	bstr_t name;
	bstr_t identifier;
	bstr_t description;
	bstr_t type;
	std::vector<bstr_t> resourceIds;

	BEGIN_METADATA(Cell)
		STDFLD(identifier, type_is_bstr_t),
		STDFLD(name, type_is_bstr_t),
		STDFLD(type, type_is_bstr_t),
		STDFLD(resourceIds, type_is_array),
		STDFLD(properties, type_is_propertylist),
		STDFLD(description, type_is_bstr_t),
		END_METADATA;

};
struct Layout : public IObject
{
	Layout();
	void Load(MSXML2::IXMLDOMNodePtr  ini);
	void Save(CMSD::CLayout &layout);
	bstr_t identifier;
	bstr_t name;
	bstr_t description;
	bstr_t associatedResource;
	bstr_t unit;
	bstr_t boundaryWidth;
	bstr_t boundaryDepth;
	bstr_t placementX;
	bstr_t placementY;
	bstr_t CoordinateSystem;

	BEGIN_METADATA(Layout)
		STDFLD(identifier, type_is_bstr_t),
		STDFLD(name, type_is_bstr_t),
		STDFLD(associatedResource, type_is_bstr_t),
		STDFLD(unit, type_is_bstr_t),
		STDFLD(boundaryWidth, type_is_bstr_t),
		STDFLD(boundaryDepth, type_is_bstr_t),
		STDFLD(CoordinateSystem, type_is_bstr_t),
		STDFLD(placementX, type_is_bstr_t),
		STDFLD(placementY, type_is_bstr_t),
		STDFLD(properties, type_is_propertylist),
		STDFLD(description, type_is_bstr_t),
		END_METADATA;
}; 

struct Part   : public IObject
{
public:
	Part();
	void Load(MSXML2::IXMLDOMNodePtr  ini);
	void Save(CMSD::CPartType &partType);
	bool IsEmpty() { return name == _bstr_t(L"None"); }
	bstr_t name;
	bstr_t identifier;
	bstr_t description;
	bstr_t BOM;
	bstr_t processplanidentifier;
	bstr_t billOfMaterialsIdentifier;
	bstr_t width, depth, height;
	bstr_t sizeunits;
	bstr_t weight;
	bstr_t weightunits;

	Distribution arrivals;
	//std::vector<PropertyElement> simpleproperties;

	BEGIN_METADATA(Part)
		STDFLD(identifier, type_is_bstr_t),
		STDFLD(name, type_is_bstr_t),
		STDFLD(processplanidentifier, type_is_bstr_t), // actually menu selection
		STDFLD(width, type_is_bstr_t),
		STDFLD(depth, type_is_bstr_t),
		STDFLD(height, type_is_bstr_t),
		STDFLD(sizeunits, type_is_bstr_t),
		STDFLD(weight, type_is_bstr_t),
		STDFLD(weight, type_is_bstr_t),
		STDFLD(weightunits, type_is_bstr_t),
		STDFLD(properties, type_is_propertylist),
		STDFLD(description, type_is_bstr_t),
		END_METADATA;

};

struct Process : public IObject
{
	Process();
	void Load(MSXML2::IXMLDOMNodePtr  ini);
	void Save(CMSD::CProcess &partType);

	bool IsEmpty() { return identifier == _bstr_t(L"None"); }

	bstr_t identifier;
	std::vector<bstr_t> resourcesRequired;
	Time setupTime;
	Time operationTime;
	bstr_t scrapPercentage;
	bstr_t partsProducedId;
	bstr_t partsProducedQuantity;
	bstr_t partsConsumedId;
	bstr_t partsConsumedQuantity;
	bstr_t type;
	bstr_t description;
	bstr_t repetitionCount;
	bstr_t machineProgramInformation;

	BEGIN_METADATA(Process)
		STDFLD(identifier, type_is_bstr_t),
		STDFLD(type, type_is_bstr_t),
		STDFLD(resourcesRequired, type_is_array),
		STDFLD(description, type_is_bstr_t),
		STDFLD(repetitionCount, type_is_bstr_t),
		STDFLD(machineProgramInformation, type_is_bstr_t),
		STDFLD(operationTime.time, type_is_bstr_t),
		STDFLD(operationTime.units, type_is_bstr_t),
		STDFLD(setupTime.time, type_is_bstr_t),
		STDFLD(setupTime.units, type_is_bstr_t),
		MENUFLD(partsProducedId, type_is_menu, &Part::_objects, "identifier"),
		STDFLD(partsProducedQuantity, type_is_bstr_t),
		STDFLD(partsConsumedId, type_is_bstr_t),
		STDFLD(partsConsumedQuantity, type_is_bstr_t),
		STDFLD(properties, type_is_propertylist),
		END_METADATA
};

struct ProcessPlan : public IObject
{
	ProcessPlan();
	void Load(MSXML2::IXMLDOMNodePtr  ini);
	void Save(CMSD::CProcessPlan &partType);
	bool IsEmpty() { return identifier == _bstr_t(L"None"); }
	bool IsSequence() { return steps.size() > 0; }
	bstr_t identifier;
	bstr_t firstProcessId;
	std::vector<bstr_t> partsProduced;
	std::vector<bstr_t> partsConsumed;
	std::vector<bstr_t> processIds;
	std::vector<ProcessPtr> processes;
	Process* FindProcess(bstr_t name);
	std::vector<bstr_t> steps;
	//bstr_t repetitionCount;
	bstr_t processSequenceName;

	BEGIN_METADATA(ProcessPlan)
		STDFLD(identifier, type_is_bstr_t),
//		STDFLD(firstProcessId, type_is_bstr_t),
		STDFLD(partsProduced, type_is_array),
		STDFLD(partsConsumed, type_is_array),
		STDFLD(processIds, type_is_array),
		STDFLD(steps, type_is_array),
	//	STDFLD(repetitionCount, type_is_bstr_t),
		STDFLD(properties, type_is_propertylist),
	END_METADATA
};

struct Job : public IObject
{
	Job();
	void Load(MSXML2::IXMLDOMNodePtr  ini);
	void Save(CMSD::CJob &job);
	bool IsEmpty() { return name == _bstr_t(L"None"); }
	bstr_t name;
	bstr_t identifier;
	std::vector<bstr_t> partIds;
	std::vector<bstr_t> partQuantity;

	BEGIN_METADATA(Job)
		STDFLD(identifier, type_is_bstr_t),
		STDFLD(name, type_is_bstr_t),
		STDFLD(partIds, type_is_array),
		STDFLD(partQuantity, type_is_array),
		STDFLD(properties, type_is_propertylist),
		END_METADATA
};


class CCMSDIntegrator 
{
public:
	CCMSDIntegrator(void);
	~CCMSDIntegrator(void);
	void ParseCMSD(std::string cmsdfilename);
	void SaveCMSD(std::string cmsdfilename);
	Resource* FindResourceByName(bstr_t name);
	Resource* FindResourceById(bstr_t name);
	ProcessPlan* FindProcessPlanByPart(bstr_t name);
	Layout* FindLayoutByAssociatedResource(bstr_t name);
	static Distribution* FindDistributionById(bstr_t name);
	Cell* FindCellById(bstr_t id);
	Part* FindPartById(bstr_t name);
	///////////////////
	static bstr_t GetProperty(MSXML2::IXMLDOMNodePtr pNode,bstr_t PropName, bstr_t defaultVal, bstr_t NodeType=L".//Property");
	//Distribution GetStatisticalProperty(MSXML2::IXMLDOMNodePtr pNode,bstr_t PropName); // return none if doesnt exist
	static MappedValues GetNameValueProperties(MSXML2::IXMLDOMNodePtr pNode, bstr_t NodeType=L".//Property");
	static bstr_t GetElement(MSXML2::IXMLDOMNodePtr pNode,bstr_t ElementName, bstr_t defaultVal=L"None");
	Distribution GetDistribution(MSXML2::IXMLDOMNodePtr pNode);

	std::vector<IObjectPtr> &resources;
	std::vector<IObjectPtr> &cells;
	std::vector<IObjectPtr> &parts;
	std::vector<IObjectPtr> &processplans;
	std::vector<IObjectPtr> &jobs;
	std::vector<IObjectPtr> &distributions;
	std::vector<IObjectPtr> &calendars;
	std::vector<IObjectPtr> &layouts;

	MSXML2::IXMLDOMDocument2Ptr        m_pXMLDoc;

	void Clear()
	{
		for(int i=0; i< IObject::GetAllObjects().size(); i++)
			IObject::GetAllObjects()[i]->clear();
	}
};
