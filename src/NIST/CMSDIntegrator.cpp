#include "StdAfx.h"
#include <algorithm>
#include "CMSDIntegrator.h"

  
IMPLEMENT_METADATA(Part);
IMPLEMENT_METADATA(Resource);
IMPLEMENT_METADATA(ProcessPlan);
IMPLEMENT_METADATA(Job);
IMPLEMENT_METADATA(Schedule);
IMPLEMENT_METADATA(Shift);
IMPLEMENT_METADATA(Calendar);
IMPLEMENT_METADATA(Cell);
IMPLEMENT_METADATA(Process);
IMPLEMENT_METADATA(Layout);
IMPLEMENT_METADATA(Distribution);
IMPLEMENT_METADATA(CostAllocation);
IMPLEMENT_METADATA(Documentation);

//IMPLEMENT_METADATA(PropertyElement);

std::map<bstr_t, Distribution> Distribution::distributions;
static _bstr_t checkParseError(MSXML2::IXMLDOMParseErrorPtr pError)
{
	_bstr_t parseError =_bstr_t("At line ")+ _bstr_t(pError->Getline()) + _bstr_t("\n")+ _bstr_t(pError->Getreason());
	//MessageBox(NULL,parseError, "Parse Error",MB_OK);
	return parseError;

}

static 	void dump_com_error(_com_error &e)
{
	::AtlTrace("Error\n");
	//TRACE1("\a\tCode = %08lx\n", e.Error());
	//TRACE1("\a\tCode meaning = %s", e.ErrorMessage());
	_bstr_t bstrSource(e.Source());
	_bstr_t bstrDescription(e.Description());
	::AtlTrace("\a\tSource = %s\n", (LPCSTR) bstrSource);
	::AtlTrace("\a\tDescription = %s\n", (LPCSTR) bstrDescription);
}

//static  MSXML2::IXMLDOMNodePtr CreateNode(MSXML2::IXMLDOMNodePtr pNode, std::string elementname, std::string elementtext, std::string xmlns="")
//{
//   MSXML2::IXMLDOMNodePtr pElement = pNode->createNode(NODE_ELEMENT, elementname.c_str(), xmlns.c_str());
//   pElement->text = bstr_t(elementtext.c_str());
//}
_bstr_t GetAttribute(MSXML2::IXMLDOMNodePtr node, _bstr_t attribute)
{
	_bstr_t text= L"";;
	CComPtr<MSXML2::IXMLDOMNamedNodeMap> attributes;
	node->get_attributes( &attributes );
	if( attributes ) 
	{
		MSXML2::IXMLDOMNodePtr attr = attributes->getNamedItem(attribute);
		if(attr==NULL)
			return text;
		if(attr->nodeValue.vt == VT_BSTR)
			return attr->nodeValue.bstrVal;
	}

	return text;
}


///////////////////////////////////////////////////////////////////////////////////////////////
PropertyElement::PropertyElement(bstr_t _name, bstr_t _value): name(_name), value(_value), description(L"None") {  }
std::vector<bstr_t>& PropertyElement::GetTypeList()
{
	static std::vector<bstr_t> stringList;
    if (stringList.empty())
	{
		stringList.push_back(bstr_t("Name")); 
		stringList.push_back(bstr_t("Distribution")); 
		stringList.push_back(bstr_t("BillOfMaterialsComponentReference")); 
		stringList.push_back(bstr_t("BillOfMaterialsReference")); 
		stringList.push_back(bstr_t("CalendarReference")); 
		stringList.push_back(bstr_t("DistributionDefinitionReference")); 
		stringList.push_back(bstr_t("InventoryItemClassReference")); 
		stringList.push_back(bstr_t("InventoryItemReference")); 
		stringList.push_back(bstr_t("JobReference")); 
		stringList.push_back(bstr_t("LayoutElementReference")); 
		stringList.push_back(bstr_t("MaintenancePlanReference")); 
		stringList.push_back(bstr_t("MaintenanceProcessReference")); 
		stringList.push_back(bstr_t("OrderInformationReference")); 
		stringList.push_back(bstr_t("PartReference")); 
		stringList.push_back(bstr_t("PartTypeReference")); 
		stringList.push_back(bstr_t("ProcessPlanReference"));  
		stringList.push_back(bstr_t("ProcessReference"));  
		stringList.push_back(bstr_t("PropertyDescriptionReference")); 
		stringList.push_back(bstr_t("ReferenceMaterialReference")); 
		stringList.push_back(bstr_t("ResourceClassReference")); 
		stringList.push_back(bstr_t("ResourceReference")); 
		stringList.push_back(bstr_t("ScheduleInformationReference")); 
		stringList.push_back(bstr_t("SetupChangeoverReference")); 
		stringList.push_back(bstr_t("SetupDefinitionReference")); 
		stringList.push_back(bstr_t("SkillReference")); 
	}
	return stringList;
};
bool PropertyElement::GetPropertyValue(MSXML2::IXMLDOMNodePtr  ini, bstr_t &name,   bstr_t &value)
{
	CMSD::CProperty prop = ini;
	ASSIGN(name, ((std::string)prop.Name[0]).c_str(), L"None");
	ASSIGN(value, ((std::string)prop.Value2[0]).c_str(), L"None");
	if(name!=_bstr_t(L"None") &&  value!=_bstr_t(L"None"))
		return true;
	return false;
}


void PropertyElement::Load(MSXML2::IXMLDOMNodePtr  ini)
{
	CMSD::CProperty prop = ini;
	ASSIGN(name, ((std::string)prop.Name[0]).c_str(), L"None");
	ASSIGN(value, ((std::string)prop.Value2[0]).c_str(), L"None");
}
void PropertyElement::Save(CMSD::CProperty & prop)
{
	if((name == bstr_t(L"None") && value == bstr_t(L"None")) ||
		(name == bstr_t(L"") && value == bstr_t(L""))
		)
	{
		MSXML2::IXMLDOMNodePtr  pNode = prop.GetNode()->GetparentNode(); 
		pNode->removeChild(prop.GetNode()); 
		return;
	}
	prop.Name.append() = std::string((LPCSTR) this->name);
	prop.Value2.append() = std::string((LPCSTR) value);
	CREATEIF(prop.Description.append(), description);
}
bool PropertyElement::IsPropertyElement(MSXML2::IXMLDOMNodePtr  pNode)
{
	MSXML2::IXMLDOMNodePtr pNameElement = pNode->selectSingleNode(bstr_t(L"Name"));
	MSXML2::IXMLDOMNodePtr pValueElement = pNode->selectSingleNode(bstr_t(L"Value"));
	if(pNameElement!=NULL && pValueElement !=NULL)
		return true;
	return false;
}

bool PropertyElement::IsDistributionReferenceProperty(MSXML2::IXMLDOMNodePtr  pNode)
{
	MSXML2::IXMLDOMNodePtr pDistRefElement = pNode->selectSingleNode(bstr_t(L"./DistributionDefinitionReference/DistributionDefinitionIdentifier"));
	if(pDistRefElement !=NULL)
		return true;
	return false;
}
///////////////////////////////////////////////////////////////////////////////////////////////
Distribution::Distribution() 
{ 
	identifier=StdStringFormat("Distribution%d",_objects.size()).c_str();
	name=description=distreference=distname=distdescription=units=L"None"; 
	name1= value1= name2= value2= name3= value3="";
}

void Distribution::Save(CMSD::CDistributionDefinition &dist)
{
	CREATEIF(dist.Identifier.append() , identifier);	
	SaveDistribution(dist.Distribution[0]);
}

void Distribution::Save(CMSD::CProperty &prop)
{
	CREATEIF(prop.Name.append() , name);	
	CREATEIF(prop.Unit.append() , units);	
	CREATEIF(prop.Description.append() , description);	
	CMSD::CDistribution dist = prop.Distribution.append();
	SaveDistribution(dist);

}
void Distribution::SaveDistribution(CMSD::CDistribution &dist)
{
	mappedvalues.clear();
	mappedvalues[name1]=value1;
	mappedvalues[name2]=value2;
	mappedvalues[name3]=value3;
	int i=0;
	CREATEIF(dist.Name.append() , distname);	
	CREATEIF(dist.Description.append() , distdescription);	
	for(MappedValues::iterator it=mappedvalues.begin(); it!=mappedvalues.end(); it++)
	{
		CREATEIF(dist.DistributionParameter.append().Name.append(), (*it).first);
		CREATEIFBSTR(dist.DistributionParameter[i++].Value2.append().GetNode()->text, (*it).second);
		//CREATEIFBSTR(dist.Distribution[0].DistributionParameter[0].Description.append(), (*it).second);
	}
}

void Distribution::LoadProperty(MSXML2::IXMLDOMNodePtr  ini)
{
	CMSD::CProperty prop = ini;
	type="Property";
	ASSIGN(name ,((std::string) prop.Name[0]).c_str(), L"None");
	ASSIGN(description ,((std::string) prop.Description[0]).c_str(), L"None");
	ASSIGN(units ,((std::string) prop.Unit[0]).c_str(), L"None");
	LoadDistribution(prop.Distribution[0]);
}
void Distribution::LoadDefinition(MSXML2::IXMLDOMNodePtr  ini)
{
	CMSD::CDistributionDefinition distribution = ini;
	type="DistributionDefinition";
	ASSIGN(identifier ,((std::string) distribution.Identifier[0]).c_str(), L"None");
	LoadDistribution(distribution.Distribution[0]);
}

void Distribution::LoadDistribution(CMSD::CDistribution &distribution)
{
	if(distribution.GetNode() == NULL) 
		return;
	ASSIGN(distname ,((std::string) distribution.Name[0]).c_str(), L"None");
	ASSIGN(distdescription ,((std::string) distribution.Description[0]).c_str(), L"None");
	for(int i=0; i< distribution.DistributionParameter.count(); i++)
	{
		bstr_t name, value;
		ASSIGN(name ,((std::string) distribution.DistributionParameter[i].Name[0]).c_str(), L"None");
		ASSIGN(value ,((std::string) distribution.DistributionParameter[i].Value2[0].GetNode()->text).c_str(), L"None");
		mappedvalues[name]=value;
	}
	MappedValues::iterator it=mappedvalues.begin(); 
	if(it==mappedvalues.end()) return;
	name1=(*it).first;
	value1=(*it).second;
	it++; if(it==mappedvalues.end()) return;
	name2=(*it).first;
	value2=(*it).second;
	it++; if(it==mappedvalues.end()) return;
	name3=(*it).first;
	value3=(*it).second;
}
///////////////////////////////////////////////////////////////////////////////////////////////
// A manufacturing calendar is a collection of information about the shifts, shift schedules, 
// and holidays that apply to a facility over a specified time period.
CostAllocation::CostAllocation()
{
	 name=description=type=category=currencyType=L"None";
}
void CostAllocation::Load(MSXML2::IXMLDOMNodePtr  ini)
{
	CMSD::CCostAllocationData cost = ini;
	ASSIGN(name ,((std::string) cost.CostName[0]).c_str(), name);
	ASSIGN(description ,((std::string) cost.CostDescription[0]).c_str(), description);
	ASSIGN(type ,((std::string) cost.CostType[0]).c_str(), type);
	ASSIGN(category ,((std::string) cost.CostCategory[0]).c_str(), category);
	ASSIGN(currencyType ,((std::string) cost.TotalCost[0].Value2[0].GetNode()->text).c_str(), currencyType);

	PropertyElement().LoadProperties<CMSD::CCostAllocationData>(cost, properties, distributions);
}
void CostAllocation::Save(CMSD::CCostAllocationData &cost)
{
	cost.CostName.append() = std::string((LPCSTR) this->name);
	CREATEIF(cost.CostDescription.append() ,  description);
	//CREATEIFBSTR(shift.StartTime.append().GetNode()->text ,  startTime);
	//CREATEIFBSTR(shift.Duration.append().GetNode()->text ,  duration);
	//CREATEIFBSTR(shift.ApplicableDay.append().GetNode()->text ,  applicableDay);
	PropertyElement().SaveProperties<CMSD::CCostAllocationData>(cost, properties, distributions);
}

///////////////////////////////////////////////////////////////////////////////////////////////
// A manufacturing calendar is a collection of information about the shifts, shift schedules, 
// and holidays that apply to a facility over a specified time period.
Shift::Shift()
{
	identifier=StdStringFormat("Shift%d",_objects.size()).c_str();
	 description=startTime=duration=applicableDay=L"None";
}
void Shift::Load(MSXML2::IXMLDOMNodePtr  ini)
{
	CMSD::CShift shift = ini;
	ASSIGN(identifier ,((std::string) shift.Identifier[0]).c_str(), L"None");
	ASSIGN(description ,((std::string) shift.Description[0]).c_str(), L"None");
	ASSIGN(startTime ,shift.StartTime[0].GetNode()->text, L"None");
	ASSIGN(duration ,shift.Duration[0].GetNode()->text, L"None");
	ASSIGN(applicableDay ,shift.ApplicableDay[0].GetNode()->text, L"None");
	PropertyElement().LoadProperties<CMSD::CShift>(shift, properties, distributions);
}
void Shift::Save(CMSD::CShift &shift)
{
	shift.Identifier.append() = std::string((LPCSTR) this->identifier);
	CREATEIF(shift.Description.append() ,  description);
	CREATEIFBSTR(shift.StartTime.append().GetNode()->text ,  startTime);
	CREATEIFBSTR(shift.Duration.append().GetNode()->text ,  duration);
	CREATEIFBSTR(shift.ApplicableDay.append().GetNode()->text ,  applicableDay);
	PropertyElement().SaveProperties<CMSD::CShift>(shift, properties, distributions);
}
Calendar::Calendar()
{
	identifier=StdStringFormat("Calendar%d",_objects.size()).c_str();
	description=startdate=enddate=L"None";
}
void Calendar::Load(MSXML2::IXMLDOMNodePtr  ini)
{
	CMSD::CCalendar cal = ini;
	ASSIGN(identifier ,((std::string) cal.Identifier[0]).c_str(), L"None");
	ASSIGN(description ,((std::string) cal.Description[0]).c_str(), L"None");
	// FIXME: this will need to be parsed into something
	ASSIGN(startdate ,cal.EffectiveStartDate[0].GetNode()->text, L"None");
	ASSIGN(enddate ,cal.EffectiveEndDate[0].GetNode()->text, L"None");
	for(int i=0; i< cal.Shift.count(); i++)
	{
		Shift * shift ( (Shift*) Shift().CreateSave<Shift>());
		shift->Load(cal.Shift[i].GetNode()); 
		shifts.push_back(shift);
	}
	PropertyElement().LoadProperties<CMSD::CCalendar>(cal, properties, distributions);

}
void Calendar::Save(CMSD::CCalendar &cal)
{
	cal.Identifier.append() = std::string((LPCSTR) this->identifier);
	CREATEIF(cal.Description.append() ,  description);
	CREATEIFBSTR(cal.EffectiveStartDate.append().GetNode()->text ,  startdate);
	CREATEIFBSTR(cal.EffectiveEndDate.append().GetNode()->text ,  enddate);
	for(int i=0; i< shifts.size(); i++)
		shifts[i]->Save(cal.Shift.append());

	PropertyElement().SaveProperties<CMSD::CCalendar>(cal, properties, distributions);
}
int Calendar::ShiftsPerWeek()
{
	return (int) shifts.size();
}
double Calendar::HoursPerWeek()
{
	double duration=0.0;
	for(int i=0; i< shifts.size(); i++)
	{
		 duration += atof((LPCSTR) shifts[i]->duration);
	}
	return duration;
}


///////////////////////////////////////////////////////////////////////////////////////////////
Schedule::Schedule()
{
	identifier=StdStringFormat("Schedule%d",_objects.size()).c_str();
	description="";
}
void Schedule::Load(MSXML2::IXMLDOMNodePtr  ini)
{
	CMSD::CSchedule schedule = ini;
	ASSIGN(identifier ,((std::string) schedule.Identifier[0]).c_str(), L"None");
	ASSIGN(description ,((std::string) schedule.Description[0]).c_str(), L"None");
	PropertyElement().LoadProperties<CMSD::CSchedule>(schedule, properties, distributions);

}
void Schedule::Save(CMSD::CSchedule &schedule)
{
	schedule.Identifier.append() = std::string((LPCSTR) this->identifier);
	CREATEIF(schedule.Description.append() ,  description);
	PropertyElement().SaveProperties<CMSD::CSchedule>(schedule, properties, distributions);

}
///////////////////////////////////////////////////////////////////////////////////////////////
Resource::Resource()
{
	identifier=StdStringFormat("Resource%d",_objects.size()).c_str();
	//model=serial_number=capacity=name=manufacturer=
	type=description=hourlyRate=hourlyRateUnit=L"None";
	mtbfid=mttrid=L"None";
}
void  Resource::Zero()
{

	identifier = L"None";
	name= L"None";
	type= L"None";
	
	description=L"None";
	hourlyRate=L"None";
	hourlyRateUnit=L"None";

}
void Resource::Load(MSXML2::IXMLDOMNodePtr  ini)
{
	CMSD::CResource resource = ini;

	ASSIGN(name ,((std::string) resource.Name[0]).c_str(), name);
	ASSIGN(identifier ,((std::string) resource.Identifier[0]).c_str(), identifier);
	ASSIGN(type ,((std::string) resource.ResourceType[0]).c_str(), type);
	ASSIGN(description ,((std::string) resource.Description[0]).c_str(), description);
	ASSIGN(hourlyRate , resource.HourlyRate[0].Value2[0].GetNode()->text, hourlyRate);
	ASSIGN(hourlyRateUnit ,((std::string) resource.HourlyRate[0].Unit[0]).c_str(),hourlyRateUnit);

	// These are properties
//	capacity = CCMSDIntegrator::GetProperty(ini, bstr_t(L"Capacity"), bstr_t(L"1"));  
//	manufacturer = CCMSDIntegrator::GetProperty(ini, bstr_t(L"Manufacturer"), bstr_t(L"Acme"));  
//	serial_number = CCMSDIntegrator::GetProperty(ini, bstr_t(L"SerialNumber"), bstr_t(L"Acme"));  

	PropertyElement().LoadProperties<CMSD::CResource>(resource, properties, distributions);

	for(int i=0; i< resource.Property.count(); i++)
	{

		if( resource.Property[i].Name[0].GetNode()->text == bstr_t("MTBF:Measured"))
		{
			Distribution * astat ( (Distribution *) IObject::CreateSave<Distribution>() );
			astat->LoadProperty(resource.Property[i].GetNode());
			mtbfid= astat->identifier= this->identifier + "MTBF:Measured";
			this->mtbf=astat;
		}
		else if( resource.Property[i].Name[0].GetNode()->text == bstr_t("MTTR:Measured"))
		{
			Distribution * astat ( (Distribution *) IObject::CreateSave<Distribution>() );
			astat->LoadProperty(resource.Property[i].GetNode());
			mttrid= astat->identifier= this->identifier + "MTTR:Measured";
			this->mttr=astat;
		}
	}
}
void  Resource::Save(CMSD::CResource& resource)
{
	resource.Identifier.append() = std::string((LPCSTR) identifier);
	CREATEIF(resource.Name.append() ,  name);
	CREATEIF(resource.ResourceType.append() ,  type);
	CREATEIF(resource.Description.append(),  description);

	//PropertyElement(L"Capacity", capacity).Save(resource.Property.append());
	//PropertyElement(L"Manufacturer", manufacturer).Save(resource.Property.append());
	//PropertyElement(L"Serial_number", serial_number).Save(resource.Property.append());

	//for(int i=0; i< simpleproperties.size(); i++)
	//{		
	//	simpleproperties[i].Save(resource.Property.append());
	//}

	PropertyElement().SaveProperties<CMSD::CResource>(resource, properties, distributions);
	
	Distribution* mtbfdist = CCMSDIntegrator::FindDistributionById(mtbfid);
	Distribution* mttrdist = CCMSDIntegrator::FindDistributionById(mttrid);

	if(mtbfdist!=NULL)// !mtbf.IsEmpty())
		mtbfdist->Save(resource.Property.append()); // fixed: Wed 03/06/13 05:24:20 PM
	if(mttrdist!=NULL)
		mttrdist->Save(resource.Property.append());

}
///////////////////////////////////////////////////////////////////////////////////////////////
Part::Part()  
{
	identifier=StdStringFormat("Part%d",_objects.size()).c_str();
	name=BOM=processplanidentifier=billOfMaterialsIdentifier=L"None";
	description=width= depth= height=sizeunits=weight=weightunits=L"";
}
void  Part::Zero()
{

	identifier = L"None";
	processplanidentifier =L"None";
	name= L"None";
	billOfMaterialsIdentifier= L"None";
	sizeunits= L"None";
	depth= L"None";
	height=L"None";
	width=L"None";
	weight=L"None";
	weightunits=L"None";

}
void  Part::Load(MSXML2::IXMLDOMNodePtr ini)
{
	CMSD::CPartType partType = ini;
	
	ASSIGN(identifier , ((std::string)partType.Identifier[0]).c_str(), identifier);
	ASSIGN(processplanidentifier , ((std::string) partType.ProcessPlan[0].ProcessPlanIdentifier[0]).c_str(), processplanidentifier);
	ASSIGN(name, ((std::string)partType.Name[0]).c_str(), name);
	ASSIGN(billOfMaterialsIdentifier, ((std::string)partType.BillOfMaterials[0].BillOfMaterialsIdentifier[0]).c_str(), billOfMaterialsIdentifier);

	ASSIGN(sizeunits, ((std::string)partType.Size[0].Unit[0]).c_str(), sizeunits);
	ASSIGN(depth, (LPCSTR)partType.Size[0].Depth[0].GetNode()->text, depth);
	ASSIGN(height, (LPCSTR)partType.Size[0].Height[0].GetNode()->text, height);
	ASSIGN(width, (LPCSTR)partType.Size[0].Width[0].GetNode()->text, width);
	ASSIGN(weight, (LPCSTR)partType.Weight[0].Value2[0].GetNode()->text, weight);
	ASSIGN(weightunits, ((std::string)partType.Weight[0].Unit[0]).c_str(), weightunits);

	PropertyElement().LoadProperties<CMSD::CPartType>(partType, properties, distributions);  
}

void  Part::Save(CMSD::CPartType &partType)
{
	partType.Identifier.append() = std::string((LPCSTR) identifier);
	partType.ProcessPlan.append().ProcessPlanIdentifier.append() = std::string((LPCSTR) processplanidentifier);
	CREATEIF(partType.Name.append() , name);	
	CREATEIF(partType.BillOfMaterials.append().BillOfMaterialsIdentifier.append() ,  billOfMaterialsIdentifier);
	if(width.length() > 0 && depth.length() > 0 && height.length() > 0)
	{
		CMSD::CGrossDimensions size = partType.Size.append();
		size.Unit.append() =  std::string((LPCSTR) sizeunits);
		size.Width.append().GetNode()->text =   width;
		size.Depth.append().GetNode()->text =   depth; 
		size.Height.append().GetNode()->text =  height; 
	}
	if(weight.length() > 0 )
	{
		partType.Weight.append().Value2.append().GetNode()->text =   weight;
		partType.Weight[0].Unit.append() =  std::string((LPCSTR) weightunits);
	}
	
	PropertyElement().SaveProperties<CMSD::CPartType>(partType, properties, distributions);
	
}
///////////////////////////////////////////////////////////////////////////////////////////////
Cell::Cell() 
{  
	identifier=StdStringFormat("Cell%d",_objects.size()).c_str();
	name=type=description=L"None"; 
}
bool Cell::IsResourceCell(MSXML2::IXMLDOMNodePtr ini)
{
	CMSD::CResource resource = ini;
	return ( resource.GroupDefinition.count() > 0);
}
void Cell::Save(CMSD::CResource &resource)
{
	resource.Identifier.append() = std::string((LPCSTR) identifier);
	CREATEIF(resource.Name.append() ,  name);
	CREATEIF(resource.ResourceType.append() ,  type);
	CREATEIF(resource.Description.append(),  description);
	if(resourceIds.size()>0)
	{
		resource.GroupDefinition.append();
		for(int i=0; i<resourceIds.size(); i++)
		{
			CREATEIF(resource.GroupDefinition[0].ResourceGroupMember.append().ResourceIdentifier.append(), resourceIds[i]);
		}
	}
	PropertyElement().SaveProperties<CMSD::CResource>(resource, properties, distributions);
}

void  Cell::Load(MSXML2::IXMLDOMNodePtr ini)
{	
	CMSD::CResource resource = ini;
	if( resource.GroupDefinition.count() < 1)
		return;  // throw?
	ASSIGN(name ,((std::string) resource.Name[0]).c_str(), L"None");
	ASSIGN(identifier ,((std::string) resource.Identifier[0]).c_str(), L"None");
	ASSIGN(type ,((std::string) resource.ResourceType[0]).c_str(), L"None");
	ASSIGN(description ,((std::string) resource.Description[0]).c_str(), L"None");
	bstr_t resoureID;

	for(int j=0; j< resource.GroupDefinition[0].ResourceGroupMember.count(); j++)
	{
		ASSIGN(resoureID,((std::string) resource.GroupDefinition[0].ResourceGroupMember[j].ResourceIdentifier[0]).c_str(), L"None");
		resourceIds.push_back (resoureID);
	}
	PropertyElement().LoadProperties<CMSD::CResource>(resource, properties, distributions);  
}

///////////////////////////////////////////////////////////////////////////////////////////////
Process::Process() 
{ 
	identifier=StdStringFormat("Process%d",_objects.size()).c_str();
	machineProgramInformation=description=type=description=L"None"; 
	scrapPercentage=partsProducedId=partsProducedQuantity=partsConsumedId=partsConsumedQuantity=L"None";
	repetitionCount=L"1";}

void Process::Save(CMSD::CProcess &process)
{

	process.Identifier.append() = std::string((LPCSTR) identifier);
	CREATEIF(process.PartsProduced.append().PartType.append().PartTypeIdentifier.append() , partsProducedId);	
	CREATEIFBSTR(process.PartsProduced[0].PartQuantity.append().GetNode()->text , partsProducedQuantity);	
	CREATEIF(process.PartsConsumed.append().PartType.append().PartTypeIdentifier.append() , partsConsumedId);	
	CREATEIFBSTR(process.PartsConsumed[0].PartQuantity.append().GetNode()->text , partsConsumedQuantity);	
	CREATEIFBSTR(process.Description.append().GetNode()->text , description);	
	CREATEIFBSTR(process.RepetitionCount.append().GetNode()->text , repetitionCount);	
	CREATEIFBSTR(process.MachineProgramInformation.append().GetNode()->text , machineProgramInformation);	

	CREATEIFBSTR(process.OperationTime.append().Value2.append().GetNode()->text , operationTime.time);	
	CREATEIF(process.OperationTime[0].Unit.append(), operationTime.units);	
	CREATEIFBSTR(process.SetupTime.append().Value2.append().GetNode()->text , setupTime.time);	
	CREATEIF(process.SetupTime[0].Unit.append(), setupTime.units);	

	//if(steps.size() > 0)
	//{
	//	process.SubProcessGroup.append();
	//	for(int i=0; i< steps.size(); i++)
	//	{
	//		CREATEIF(process.SubProcessGroup[0].Process.append().ProcessIdentifier.append(),steps[i]);
	//	}

	//}

	if(resourcesRequired.size() > 0)
	{
		process.ResourcesRequired.append();
		for(int i=0; i< resourcesRequired.size(); i++)
		{
			CREATEIF(process.ResourcesRequired[0].Resource.append().ResourceIdentifier.append(),resourcesRequired[i]);
		}
	}
	PropertyElement().SaveProperties<CMSD::CProcess>(process, properties, distributions);
}

void Process::Load(MSXML2::IXMLDOMNodePtr  ini)
{
	CMSD::CProcess process = ini;
	ASSIGN(identifier , ((std::string) process.Identifier[0]).c_str(), L"None");
	ASSIGN(partsProducedId,((std::string) process.PartsProduced[0].PartType[0].PartTypeIdentifier[0]).c_str(),L"None");
	ASSIGN(partsProducedQuantity, process.PartsProduced[0].PartQuantity[0].GetNode()->text, L"None");
	ASSIGN(partsConsumedId,((std::string) process.PartsConsumed[0].PartType[0].PartTypeIdentifier[0]).c_str(),L"None");
	ASSIGN(partsConsumedQuantity, process.PartsConsumed[0].PartQuantity[0].GetNode()->text, L"None");
	ASSIGN(operationTime.time,process.OperationTime[0].Value2[0].GetNode()->text,L"None");
	ASSIGN(operationTime.units,((std::string) process.OperationTime[0].Unit[0]).c_str(),L"Hours");
	ASSIGN(setupTime.time,process.SetupTime[0].Value2[0].GetNode()->text,L"None");
	ASSIGN(setupTime.units,((std::string) process.SetupTime[0].Unit[0]).c_str(),L"Hours");
	ASSIGN(repetitionCount,((std::string) process.RepetitionCount[0].GetNode()->text).c_str(),L"None");
	ASSIGN(description,((std::string) process.Description[0]).c_str(),L"None");
	ASSIGN(machineProgramInformation,((std::string) process.MachineProgramInformation[0].GetNode()->text).c_str(),L"None");

// scrapPercentage is a property
	//ASSIGN(scrapPercentage,((std::string) process.ScrapPercentage[0]).c_str(),L"None");

	for(int i=0; i< process.ResourcesRequired.count(); i++)
	{
		bstr_t resourceid;// = ((std::string)process.ResourcesRequired[i].ResourceIdentifier[0]).c_str();
	    ASSIGN(resourceid,((std::string) process.ResourcesRequired[i].Resource[0].ResourceIdentifier[0]).c_str(),L"None");
		resourcesRequired.push_back(resourceid);
	}
	PropertyElement().LoadProperties<CMSD::CProcess>(process, properties, distributions);  

}
///////////////////////////////////////////////////////////////////////////////////////////////
ProcessPlan::ProcessPlan() 
{  
	identifier=StdStringFormat("ProcessPlan%d",_objects.size()).c_str();
	firstProcessId=L"None";
	processSequenceName=L"None";
	//repetitionCount=L"1";
}
void ProcessPlan::Save(CMSD::CProcessPlan &processplan)
{
	CREATEIF(processplan.Identifier.append() , identifier);	
	CREATEIF(processplan.FirstProcess.append().ProcessIdentifier.append() , firstProcessId);	
	//CREATEIFBSTR(processplan.RepetitionCount.append().GetNode()->text , repetitionCount);	

	// Assign process sequence
	if(processSequenceName!=bstr_t(L"None"))
	{
		CMSD::CProcess process = processplan.Process.append();
		process.Identifier.append() = std::string((LPCSTR) processSequenceName);
		//CREATEIFBSTR(process.RepetitionCount.append().GetNode()->text , repetitionCount);	
		if(steps.size() > 0)
		{
			process.SubProcessGroup.append();
			for(int i=0; i< steps.size(); i++)
			{
				CREATEIF(process.SubProcessGroup[0].Process.append().ProcessIdentifier.append(),steps[i]);
			}
		}
	}
	for(int i=0; i< this->processIds.size(); i++)
	{
		Process * process =	FindProcess(processIds[i]);
		if(process!=NULL)
			process->Save(processplan.Process.append());
	}
	PropertyElement().SaveProperties<CMSD::CProcessPlan>(processplan, properties, distributions);
}

void ProcessPlan::Load(MSXML2::IXMLDOMNodePtr  ini)
{
	CMSD::CProcessPlan pp = ini;
	ASSIGN(identifier ,((std::string) pp.Identifier[0]).c_str(), L"None");
	ASSIGN(firstProcessId ,((std::string) pp.FirstProcess[0].ProcessIdentifier[0]).c_str(), L"None");
	//ASSIGN(repetitionCount, pp.RepetitionCount[0].GetNode()->text,L"None");
	for(int i=0; i<pp.Process.count();i++)
	{
		// If its a sequence process, push into process plan, and continue
		if(pp.Process[i].SubProcessGroup.count()>0)
		{
			ASSIGN(processSequenceName , ((std::string) pp.Process[i].Identifier[0]).c_str(), L"None");
			for(int j=0; j< pp.Process[i].SubProcessGroup[0].Process.count(); j++)
			{
				bstr_t processid;// = ((std::string)process.SubProcessGroup[i].ResourceIdentifier[0]).c_str();
				ASSIGN(processid,((std::string) pp.Process[i].SubProcessGroup[0].Process[j].ProcessIdentifier[0]).c_str(),L"None");
				if(processid!=bstr_t(L"None"))
					steps.push_back(processid);
			}
			continue;
		}

		Process* process ( (Process *)  IObject::CreateSave<Process>());
		process->Load(pp.Process[i].GetNode());
		processes.push_back(process);
		processIds.push_back(process->identifier);
	}
	PropertyElement().LoadProperties<CMSD::CProcessPlan>(pp, properties, distributions);  
}
Process * ProcessPlan::FindProcess(bstr_t name)
{
	Process* process;
	for(int i=0; i< this->processes.size(); i++)
	{
		process=(Process *) processes[i];//.get();
		if(process->identifier == name)
			return process;
	}
	return process;
}

///////////////////////////////////////////////////////////////////////////////////////////////
Job::Job() 
{  
	identifier=StdStringFormat("Job%d",_objects.size()).c_str();
	name=L"None"; 
}

void Job::Load(MSXML2::IXMLDOMNodePtr  ini)
{
	CMSD::CJob job = ini;
	ASSIGN(identifier ,((std::string) job.Identifier[0]).c_str(), L"None");

	bstr_t val;
	for(int i=0; i< job.PlannedEffort.count(); i++)
	{
		ASSIGN(val ,((std::string) job.PlannedEffort[i].PartsProduced[0].PartType[0].PartTypeIdentifier[0]).c_str(), L"None");
		partIds.push_back(val);
		ASSIGN(val ,((std::string) job.PlannedEffort[i].PartsProduced[0].PartQuantity[0].GetNode()->text).c_str(), L"None");
		partQuantity.push_back(val);
	}
	PropertyElement().LoadProperties<CMSD::CJob>(job, properties, distributions);  
}
void Job::Save(CMSD::CJob &job)
{
	CREATEIF(job.Identifier.append() , identifier);	
	for(int i=0; i< partIds.size(); i++)
	{
		CREATEIF(job.PlannedEffort.append().PartsProduced.append().PartType.append().PartTypeIdentifier.append(), partIds[i]);
		CREATEIFBSTR(job.PlannedEffort[i].PartsProduced[0].PartQuantity.append().GetNode()->text, partQuantity[i]);

	}
	PropertyElement().SaveProperties<CMSD::CJob>(job, properties, distributions);
}

///////////////////////////////////////////////////////////////////////////////////////////////
Layout::Layout()
{
	identifier=StdStringFormat("Layout%d",_objects.size()).c_str();
	unit=CoordinateSystem=name=description=associatedResource=boundaryWidth=boundaryDepth=placementX=placementY=L"None";
}
void Layout::Load(MSXML2::IXMLDOMNodePtr  ini)
{
	CMSD::CLayout layout=ini;
	ASSIGN(identifier ,((std::string) layout.Identifier[0]).c_str(), L"None");
	ASSIGN(name ,((std::string) layout.Name[0]).c_str(), L"None");
	ASSIGN(description ,((std::string) layout.Description[0]).c_str(), L"None");
	ASSIGN(associatedResource ,((std::string) layout.AssociatedResource[0].ResourceIdentifier[0]).c_str(), L"None");
	ASSIGN(unit ,((std::string) layout.Boundary[0].Unit[0]).c_str(), L"None");
	ASSIGN(boundaryWidth , layout.Boundary[0].Width[0].GetNode()->text, L"None");
	ASSIGN(boundaryDepth , layout.Boundary[0].Depth[0].GetNode()->text, L"None");
	ASSIGN(CoordinateSystem ,((std::string) layout.Boundary[0].CoordinateSystem[0]).c_str(), L"None");
	ASSIGN(placementX , layout.Placement[0].Location[0].X[0].GetNode()->text, L"None");
	ASSIGN(placementY , layout.Placement[0].Location[0].Y[0].GetNode()->text, L"None");
	PropertyElement().LoadProperties<CMSD::CLayout>(layout, properties, distributions);  

}
void Layout::Save(CMSD::CLayout &layout)
{
	CREATEIF(layout.Identifier.append() , identifier);	
	CREATEIF(layout.Name.append() , name);	
	CREATEIF(layout.Description.append() , description);	
	CREATEIF(layout.AssociatedResource.append().ResourceIdentifier.append() , associatedResource);	
	CREATEIFBSTR(layout.Boundary.append().Width.append().GetNode()->text , boundaryWidth);	
	CREATEIFBSTR(layout.Boundary[0].Depth.append().GetNode()->text , boundaryDepth);	
	CREATEIF(layout.Boundary[0].Unit.append(), unit);	
	CREATEIF(layout.Boundary[0].CoordinateSystem.append() , CoordinateSystem);	
	CREATEIFBSTR(layout.Placement.append().Location.append().X.append().GetNode()->text , placementX);	
	CREATEIFBSTR(layout.Placement[0].Location[0].Y.append().GetNode()->text , placementY);	
	PropertyElement().SaveProperties<CMSD::CLayout>(layout, properties, distributions); 
}

///////////////////////////////////////////////////////////////////////////////////////////////
Documentation::Documentation()
{
	description=L"None";
}
void Documentation::Load(MSXML2::IXMLDOMNodePtr  ini)
{
	CMSD::xs::CstringType doc=ini;
	ASSIGN(description ,((std::string) doc).c_str(), description);
}
void Documentation::Save(CMSD::CCMSDDocumentReference &doc)
{
	CREATEIF(doc.Description.append() , description);
}

///////////////////////////////////////////////////////////////////////////////////////////////
CCMSDIntegrator::CCMSDIntegrator(void)
:
		resources(Resource().objectsPtr()),
		cells(Cell().objectsPtr()),
		parts(Part().objectsPtr()),
		processplans(ProcessPlan().objectsPtr()),
		jobs(Job().objectsPtr()),
		distributions( Distribution().objectsPtr()),
		calendars( Calendar().objectsPtr()),
		layouts(Layout().objectsPtr()),
		costs(CostAllocation().objectsPtr()),
		documentation(Documentation().objectsPtr())

{
}

CCMSDIntegrator::~CCMSDIntegrator(void)
{
}

Resource* CCMSDIntegrator::FindResourceByName(bstr_t name)
{
	for(int i=0; i< resources->size(); i++)
	{
		Resource* resource ( (Resource *) resources->at(i).get());
		if(resource->name==name)
			return resource;

	}
	return NULL;
	//throw std::exception("Resource not Found\n");
}
Cell* CCMSDIntegrator::FindCellById(bstr_t id)
{
	for(int i=0; i< cells->size(); i++)
	{
		Cell* cell ( (Cell *) cells->at(i).get());
		if(cell->identifier==id)
			return cell;

	}
	return NULL;
	//throw std::exception("Resource not Found\n");
}
Distribution* CCMSDIntegrator::FindDistributionById(bstr_t id)
{
	Distribution * dist = IObject::Create<Distribution>() ;
	for(int i=0; i< dist->objects().size(); i++)
	{
		Distribution* distribution ( (Distribution *) dist->objects()[i].get());
		if(distribution->identifier==id)
			return distribution;

	}
	return NULL;
}
Resource * CCMSDIntegrator::FindResourceById(bstr_t id)
{
	for(int i=0; i< resources->size(); i++)
	{
		Resource * resource ( (Resource *) resources->at(i).get());
		if(resource->identifier==id)
			return resource;

	}
	return NULL;
//	throw std::exception("Resource not Found\n");
}
Part * CCMSDIntegrator::FindPartById(bstr_t id)
{
	for(int i=0; i< parts->size(); i++)
	{
		Part * part ( (Part *) parts->at(i).get());
		if(part->identifier==id)
			return part;

	}
	return NULL;
	//throw std::exception("Part not Found\n");
}
Layout* CCMSDIntegrator::FindLayoutByAssociatedResource(bstr_t name)
{
	for(int i=0; i< layouts->size(); i++)
	{
		Layout * layout ( (Layout *) layouts->at(i).get());
		if(layout->associatedResource==name)
			return layout;
	}
	return NULL;
//	throw std::exception("Part not Found\n");
}
ProcessPlan* CCMSDIntegrator::FindProcessPlanById(bstr_t id)
{

	for(int i=0; i< processplans->size(); i++)
	{
		ProcessPlan *processplan((ProcessPlan *) processplans->at(i).get());
		if(processplan->identifier == id)
			return processplan;

	}
	return NULL;
//	throw std::exception("FindProcessPlanById not Found\n");
}

ProcessPlan * CCMSDIntegrator::FindProcessPlanByPart(bstr_t name)
{
	for(int i=0; i< processplans->size(); i++)
	{
		ProcessPlan *processplan((ProcessPlan *) processplans->at(i).get());
		std::vector<bstr_t>::iterator it;
		it = std::find(processplan->partsProduced.begin(),processplan->partsProduced.end(), name);
		if(it!=processplan->partsProduced.end())
			return (ProcessPlan *) processplan;

	}
	//return ProcessPlan();
	return NULL;
//	throw std::exception("ProcessPlan not Found\n");
}

CostAllocation *  CCMSDIntegrator::FindCostByName(bstr_t name)
{
	for(int i=0; i< costs->size(); i++)
	{
		CostAllocation *cost((CostAllocation *) costs->at(i).get());
		if(cost->name == name)
			return cost;
	}
	return NULL;
}

Job * CCMSDIntegrator::FindJobById(bstr_t id)
{
	for(int i=0; i< jobs->size(); i++)
	{
		Job *job((Job *) jobs->at(i).get());
		if(job->identifier == id)
			return job;
	}
	return NULL;
}

bstr_t CCMSDIntegrator::GetProperty(MSXML2::IXMLDOMNodePtr pNode,bstr_t PropName, bstr_t defaultVal, bstr_t NodeType)
{
	MSXML2::IXMLDOMNodeListPtr properties = pNode->selectNodes(NodeType);
	for(int j=0; j< properties->length; j++)
	{
		MSXML2::IXMLDOMNodePtr pProp = NULL;					
		properties->get_item(j, &pProp);
		MSXML2::IXMLDOMNodePtr pName = pProp->selectSingleNode(bstr_t(".//Name"));
		MSXML2::IXMLDOMNodePtr pValue = pProp->selectSingleNode(bstr_t(".//Value"));
		bstr_t propName =  (pName!=NULL) ? pName->Gettext() : L"None";
		if( propName == PropName)
		{
			return (pValue!=NULL) ? pValue->Gettext() : defaultVal;
		}
	}
	return defaultVal;
}

bstr_t CCMSDIntegrator::GetElement(MSXML2::IXMLDOMNodePtr pNode,bstr_t ElementName, bstr_t defaultVal)
{
	MSXML2::IXMLDOMNodePtr pElement = pNode->selectSingleNode(ElementName);
	return (pElement!=NULL) ? pElement->Gettext() : defaultVal;
}

MappedValues CCMSDIntegrator::GetNameValueProperties(MSXML2::IXMLDOMNodePtr pNode, bstr_t NodeType)
{
	MappedValues namedvalues;
	MSXML2::IXMLDOMNodeListPtr properties= pNode->selectNodes(NodeType);
	for(int j=0; j< properties->length; j++)
	{
		MSXML2::IXMLDOMNodePtr pProp = NULL;					
		properties->get_item(j, &pProp);
		MSXML2::IXMLDOMNodePtr pName = pProp->selectSingleNode(bstr_t(".//Name"));
		MSXML2::IXMLDOMNodePtr pValue = pProp->selectSingleNode(bstr_t(".//Value"));
		bstr_t propName =  (pName!=NULL) ? pName->Gettext() : L"None";
		bstr_t propValue = (pValue!=NULL) ? pValue->Gettext() :  L"None";
		if( propName != bstr_t(L"None") && propValue != bstr_t(L"None"))
		{
			namedvalues[propName]=propValue;
		}
	}
	return namedvalues;
}

Distribution CCMSDIntegrator::GetDistribution(MSXML2::IXMLDOMNodePtr pNode)
{
	Distribution d;
	d.name = GetElement( pNode, bstr_t(".//Name"));
	d.units = GetElement(pNode, bstr_t(L"Unit"), bstr_t(L"Hour"));  
	d.distname = GetElement(pNode, bstr_t(L".//Distribution/Name"), bstr_t(L"None"));  
	d.mappedvalues = GetNameValueProperties(pNode, L".//DistributionParameter")	;	
	d.distreference = GetElement(pNode, bstr_t(L".//DistributionDefinitionReference/DistributionDefinitionIdentifier"), bstr_t(L"None"));  
	return d;
}

std::string CCMSDIntegrator::SaveCMSD()
{
	CMSD::CCMSD doc = CMSD::CCMSD::CreateDocument();
	CMSD::CCMSDDocument cmsddocument = doc.CMSDDocument.append();
	CMSD::CDataSectionType2  data  = cmsddocument.DataSection.append();
	for(int i=0; i< resources->size() ; i++)
	{
		Resource * resource = (Resource*)resources->at(i).get();
		resource->Save(data.Resource.append());
	}

	for(int i=0; i< parts->size() ; i++)
		((Part*)parts->at(i).get())->Save(data.PartType.append());

	for(int i=0; i< parts->size() ; i++)
		((Part*)parts->at(i).get())->Save(data.PartType.append());

	for(int i=0; i< processplans->size() ; i++)
		((ProcessPlan*)processplans->at(i).get())->Save(data.ProcessPlan.append());

	for(int i=0; i< jobs->size() ; i++)
		((Job*)jobs->at(i).get())->Save(data.Job.append());

	for(int i=0; i< distributions->size() ; i++)
		((Distribution*)distributions->at(i).get())->Save(data.DistributionDefinition.append());
	
	for(int i=0; i< calendars->size() ; i++)
		((Calendar*)calendars->at(i).get())->Save(data.Calendar.append());
	
	for(int i=0; i< layouts->size() ; i++)
		((Layout*)layouts->at(i).get())->Save(data.Layout.append());
	
	if(costs->size() > 0)
	{
		CMSD::CJobEffortDescription  jobeffort = data.Job.append().PlannedEffort.append() ;

		for(int i=0; i< costs->size() ; i++)
			((CostAllocation*)costs->at(i).get())->Save(jobeffort.CostAllocationData.append());
	}
	return doc.SaveToString(true);
}
void CCMSDIntegrator::SaveCMSD(std::string filename)
{
	std::string str=SaveCMSD();
	WriteFile(filename.c_str(), str);
}
void CCMSDIntegrator::ParseCMSD(std::string filename)
{

	CMSD::CCMSD doc = CMSD::CCMSD::LoadFromFile(filename);
	doc.SaveToFile((::ExeDirectory() + "Test1.xml").c_str(), true);
	//CMSD::CCMSD::DataSection d = doc.DataSection().first();
	CMSD::CwhiteSpaceType root = doc.whiteSpace.first();
	CMSD::CCMSDDocument cmsddocument = doc.CMSDDocument[0];
	CMSD::CHeaderSection  header  = cmsddocument.HeaderSection[0];
	CMSD::CDataSectionType2  data  = cmsddocument.DataSection[0];

	for(int i=0; i< data.PartType.count() ; i++)
	{
		Part * apart ( (Part*) Part().CreateSave<Part>());
		apart->Zero();
		apart->Load(data.PartType[i].GetNode());
		//std::vector<IObjectPtr> &someparts ( apart->objects());
		//Part * part2=(Part *) someparts[0].get();
	}
	//if(header.GetNode() != NULL)
	for(int i=0; i< header.Description.count() ; i++)
	{
		Documentation * adoc ( (Documentation*) Documentation().CreateSave<Documentation>());
		adoc->Load(header.Description[i].GetNode());
	}
	

	for(int i=0; i< data.ProcessPlan.count() ; i++)
	{
		ProcessPlan * aplan ( (ProcessPlan *) IObject::CreateSave<ProcessPlan>());
		aplan->Load(data.ProcessPlan[i].GetNode());
	}
	

	for(int i=0; i< data.Resource.count() ; i++)
	{
		if(Cell::IsResourceCell(data.Resource[i].GetNode()))
		{
			Cell * acell( (Cell *) IObject::CreateSave<Cell>());
			acell->Load(data.Resource[i].GetNode());
		}
		else
		{
			Resource * aresource  ((Resource *) IObject::CreateSave<Resource>());
			aresource->Zero();
			aresource->Load(data.Resource[i].GetNode());
		}
	}
	for(int i=0; i< data.Job.count() ; i++)
	{
		Job * ajob  ( IObject::CreateSave<Job>() );
		ajob->Load(data.Job[i].GetNode());
	}
	for(int i=0; i< data.DistributionDefinition.count() ; i++)
	{
		Distribution * astat ( (Distribution *) IObject::CreateSave<Distribution>() );
		astat->LoadDefinition(data.DistributionDefinition[i].GetNode());
	}
	for(int i=0; i< data.Calendar.count() ; i++)
	{
		Calendar *  calendar ( (Calendar *) IObject::CreateSave<Calendar>());
		calendar->Load(data.Calendar[i].GetNode());
	}
	for(int i=0; i< data.Layout.count() ; i++)
	{
		Layout * layout ((Layout *)  IObject::CreateSave<Layout>());
		layout->Load(data.Layout[i].GetNode());
	}
	//CMSD::CInventoryItem inv = data.InventoryItem[0];
	//inv.Location
	if( data.Job.count() > 0 && data.Job[0].PlannedEffort.count()>0)
	{
		for(int i=0; i< data.Job[0].PlannedEffort[0].CostAllocationData.count() ; i++)
		{
			CostAllocation * acost ( (CostAllocation *) IObject::CreateSave<CostAllocation>());
			acost->Load(data.Job[0].PlannedEffort[0].CostAllocationData[i].GetNode());
		}
	}
	int j=0;
}

void CCMSDIntegrator::MergeCMSD(std::string filename)
{

	CMSD::CCMSD doc = CMSD::CCMSD::LoadFromFile(filename);
	doc.SaveToFile((::ExeDirectory() + "Test1.xml").c_str(), true);
	//CMSD::CCMSD::DataSection d = doc.DataSection().first();
	CMSD::CwhiteSpaceType root = doc.whiteSpace.first();
	CMSD::CCMSDDocument cmsddocument = doc.CMSDDocument[0];
	CMSD::CDataSectionType2  data  = cmsddocument.DataSection[0];


	for(int i=0; i< data.PartType.count() ; i++)
	{
		std::string str = ((std::string)data.PartType[i].Identifier[0]).c_str();
		Part* apart = FindPartById((LPCSTR) str.c_str());
		if(apart==NULL)
		{
			Part * apart ( (Part*) Part().CreateSave<Part>());
			apart->Zero();
			apart->Load(data.PartType[i].GetNode());
		}
		else
		{


		}
	}

	for(int i=0; i< data.Job.count() ; i++)
	{
		std::string str = ((std::string)data.Job[i].Identifier[0]).c_str();
		Job* ajob = FindJobById((LPCSTR) str.c_str());

		if(ajob==NULL)
		{
			ajob=  ( IObject::CreateSave<Job>() );
			ajob->Load(data.Job[i].GetNode());
		}
		else
		{
			ajob->Load(data.Job[i].GetNode());
		}
	}


#if 0
	for(int i=0; i< data.ProcessPlan.count() ; i++)
	{
		ProcessPlan * aplan ( (ProcessPlan *) IObject::CreateSave<ProcessPlan>());
		aplan->Load(data.ProcessPlan[i].GetNode());
	}
#endif
	for(int i=0; i< data.Resource.count() ; i++)
	{
		if(!Cell::IsResourceCell(data.Resource[i].GetNode()))
		{
			std::string str = ((std::string)data.Resource[i].Identifier[0]).c_str();
			Resource* aresource = FindResourceById((LPCSTR) str.c_str());
			if(aresource!=NULL)
			{

				aresource->Load(data.Resource[i].GetNode());

			}
		}
#if 0
		if(Cell::IsResourceCell(data.Resource[i].GetNode()))
		{
			Cell * acell( (Cell *) IObject::CreateSave<Cell>());
			acell->Load(data.Resource[i].GetNode());
		}
		else
		{
			Resource * aresource  ((Resource *) IObject::CreateSave<Resource>());
			aresource->Load(data.Resource[i].GetNode());
		}
#endif
	}
#if 0

	for(int i=0; i< data.DistributionDefinition.count() ; i++)
	{
		Distribution * astat ( (Distribution *) IObject::CreateSave<Distribution>() );
		astat->LoadDefinition(data.DistributionDefinition[i].GetNode());
	}
	for(int i=0; i< data.Calendar.count() ; i++)
	{
		Calendar *  calendar ( (Calendar *) IObject::CreateSave<Calendar>());
		calendar->Load(data.Calendar[i].GetNode());
	}
	for(int i=0; i< data.Layout.count() ; i++)
	{
		Layout * layout ((Layout *)  IObject::CreateSave<Layout>());
		layout->Load(data.Layout[i].GetNode());
	}
#endif


	int j=0;
}


bstr_t Distribution::MapArenaDistribution() 
{
	CComBSTR bstr;
	// See if distribution reference.
	// FIXME: check if distreference exists in distributions
	MappedValues & mymappedvalues(this->mappedvalues);
	if(distreference!=_bstr_t(L"None"))
	{
		bstr = (BSTR) distributions[distreference].distname;
		mymappedvalues=MappedValues(distributions[distreference].mappedvalues);
	}
	else 
		bstr = (BSTR) distname;

	bstr.ToLower();
	bstr_t arenaexpr;
	if(bstr ==  L"exponential")
	{
		arenaexpr=L"EXPO(" + mymappedvalues[L"mean"] + L")";
		
	}
	if(bstr ==  L"poisson")
	{
		arenaexpr=L"POIS(" + mymappedvalues[L"mean"] + L")";
		
	}
	else	if(bstr ==  L"normal")
	{
		arenaexpr=L"NORM(" + mymappedvalues[L"mean"] +  L"," + mymappedvalues[L"deviation"] + L")";
		
	}
	else if(bstr == L"weibull")
	{
		arenaexpr=L"WEIB(" + mymappedvalues[L"scale"] + L"," + mymappedvalues[L"shape"] + ")";
	}
	else if(bstr == L"gamma")
	{
		arenaexpr=L"GAMM(" + mappedvalues[L"scale"] + L"," + mappedvalues[L"shape"] + ")";
	}
	else if(bstr == L"triagle")
	{
		arenaexpr=L"TRIA(" + mymappedvalues[L"minimum"] + L"," ;
		arenaexpr+=  mymappedvalues[L"mode"] + L",";
		arenaexpr+= mymappedvalues[L"maximum"] + L")";
	}
	return arenaexpr;
}

std::string CCMSDAsset::GenerateSinglePartJobXml(CCMSDIntegrator * __cmsd, std::string partid)
{
	//CCMSDAsset jobtracking;

	// Create new job with only one part from larger job
	Job * ajob= new Job();
	ajob->identifier = "job-1";
	ajob->partIds.push_back((LPCSTR) partid.c_str());
	ajob->partQuantity.push_back("1");
	this->jobs->push_back(IObjectPtr((IObject *) ajob));

	// Part
	Part *  bpart ;
	try {
	  bpart = __cmsd->FindPartById((LPCSTR) partid.c_str());
	} catch(...) {
				DebugBreak();

	}
	Part * apart = new Part();
	if(bpart==NULL)
	{
		DebugBreak();
		return "";
	}
	apart->Copy(bpart);	
	this->parts->push_back(IObjectPtr((IObject *) bpart));

	// ProcessPlan
	ProcessPlan * plan = new ProcessPlan();
	plan = __cmsd->FindProcessPlanById(bpart->processplanidentifier);	
	this->processplans->push_back(IObjectPtr((IObject *) plan));

	// Each cell for each process
	std::vector<bstr_t> steps = plan->steps;
	for(int i=0; i< steps.size(); i++)
	{
		Process* process = plan->FindProcess(steps[i]);
		if(process==NULL)
			continue;
		Cell * acell = __cmsd->FindCellById((LPCSTR) process->resourcesRequired[0]);
		if(acell!=NULL)
			this->cells->push_back(IObjectPtr((IObject *) IObject::CreateCopy<Cell>(acell)));

		for(int j=0; j< acell->resourceIds.size(); j++)
		{
			Resource * equip = __cmsd->FindResourceById(acell->resourceIds[j]);
			if(equip!=NULL)
				this->resources->push_back(IObjectPtr((IObject *) IObject::CreateCopy<Resource>(equip)));
		}
	}

	return this->SaveCMSD();
}
#include "MTCAgentCmd.h"
void CCMSDAsset::WriteToAgent(std::string aBody, std::string _device, AgentConfiguration * _config)
{

	//std::string aBody = "<Part><Inspection><MeasurementResults/></Inspection></Part>";
	std::string aId="BORE_1232";
	std::string type="Job";
	Device *device = _config->getAgent()->getDeviceByName(_device);

	_config->getAgent()->addAsset(device, aId, aBody, type);


}