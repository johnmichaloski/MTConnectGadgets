#include "StdAfx.h"
#include "ResourceIntegrator.h"
#include <algorithm>

std::map<bstr_t, Distribution> Distribution::distributions;


Resource::Resource()
{
	serial_number=L"None";
	capacity=L"None";
	name=L"None";
	manufacturer=L"None";
	identifier=L"None";
}

Part::Part()
{
	name=L"None";
	identifier=L"None";
	BOM=L"None";
	processplanidentifier=L"None";
}

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


CResourceIntegrator::CResourceIntegrator(void)
{
}

CResourceIntegrator::~CResourceIntegrator(void)
{
}

Resource & CResourceIntegrator::FindResourceByName(bstr_t name)
{
	for(int i=0; i< resources.size(); i++)
	{
		if(resources[i].name==name)
			return resources[i];

	}
	throw std::exception("Resource not Found\n");
}
Cell & CResourceIntegrator::FindCellById(bstr_t id)
{
	for(int i=0; i< cells.size(); i++)
	{
		if(cells[i].identifier==id)
			return cells[i];

	}
	throw std::exception("Resource not Found\n");
}

Resource & CResourceIntegrator::FindResourceById(bstr_t id)
{
	for(int i=0; i< resources.size(); i++)
	{
		if(resources[i].identifier==id)
			return resources[i];

	}
	throw std::exception("Resource not Found\n");
}
Part & CResourceIntegrator::FindPartById(bstr_t id)
{
	for(int i=0; i< parts.size(); i++)
	{
		if(parts[i].identifier==id)
			return parts[i];

	}
	throw std::exception("Part not Found\n");
}


ProcessPlan & CResourceIntegrator::FindProcessPlanByPart(bstr_t name)
{
	for(int i=0; i< processplans.size(); i++)
	{
		std::vector<bstr_t>::iterator it;
		it = std::find(processplans[i].partsProduced.begin(),processplans[i].partsProduced.end(), name);
		if(it!=processplans[i].partsProduced.end())
			return processplans[i];

	}
	return ProcessPlan();
	//throw std::exception("ProcessPlan not Found\n");
}

void CResourceIntegrator::ReadCmsdXmlFile(bstr_t xmlfile)
{

	_bstr_t parseError(L"");
	try{
		IXMLDOMParseErrorPtr  pError;

		// load the XML file
		// ****** you need to use IXMLDOMDocument2 interface *********
		HRESULT hr = m_pXMLDoc.CreateInstance(__uuidof(MSXML2::DOMDocument));
		m_pXMLDoc->async =  VARIANT_FALSE; 

		hr = m_pXMLDoc->load(xmlfile);      

		//check on the parser error      
		if(hr!=VARIANT_TRUE)
		{
			throw (LPCSTR) checkParseError(m_pXMLDoc->parseError);
		}

		ParseDataItems();
	}
	catch(_com_error &e)
	{
		dump_com_error(e);
		throw  e.ErrorMessage();
	}
}

bstr_t CResourceIntegrator::GetProperty(MSXML2::IXMLDOMNodePtr pNode,bstr_t PropName, bstr_t defaultVal, bstr_t NodeType)
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

bstr_t CResourceIntegrator::GetElement(MSXML2::IXMLDOMNodePtr pNode,bstr_t ElementName, bstr_t defaultVal)
{
	MSXML2::IXMLDOMNodePtr pElement = pNode->selectSingleNode(ElementName);
	return (pElement!=NULL) ? pElement->Gettext() : defaultVal;
}

MappedValues CResourceIntegrator::GetNameValueProperties(MSXML2::IXMLDOMNodePtr pNode, bstr_t NodeType)
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

Distribution CResourceIntegrator::GetDistribution(MSXML2::IXMLDOMNodePtr pNode)
{
	Distribution d;
	d.name = GetElement( pNode, bstr_t(".//Name"));
	d.units = GetElement(pNode, bstr_t(L"Unit"), bstr_t(L"Hour"));  
	d.distname = GetElement(pNode, bstr_t(L".//Distribution/Name"), bstr_t(L"None"));  
	d.mappedvalues = GetNameValueProperties(pNode, L".//DistributionParameter")	;	
	d.distreference = GetElement(pNode, bstr_t(L".//DistributionDefinitionReference/DistributionDefinitionIdentifier"), bstr_t(L"None"));  
	return d;
}

void CResourceIntegrator::ParseDataItems()
{
	MSXML2::IXMLDOMNodePtr root = m_pXMLDoc->GetdocumentElement();
	MSXML2::IXMLDOMNodeListPtr nodes = root->selectNodes(_bstr_t("//DataSection/Resource"));

	for(int i=0; i< nodes->length; i++)
	{
		Resource resource;

		MSXML2::IXMLDOMNodePtr resnode;
		MSXML2::IXMLDOMNodeListPtr properties;
		MSXML2::IXMLDOMNodePtr pNode = NULL;	

		nodes->get_item(i, &pNode);

		resnode = pNode->selectSingleNode(bstr_t(".//Name"));
		resource.name = (resnode!=NULL) ? resnode->Gettext() : L"None";
		resnode = pNode->selectSingleNode(bstr_t(".//Identifier"));
		resource.identifier = (resnode!=NULL) ? resnode->Gettext() : L"None";	

		resnode = pNode->selectSingleNode(bstr_t(".//GroupDefinition"));
		// Cell - Group of resources
		if(resnode !=NULL)
		{
			MSXML2::IXMLDOMNodeListPtr members= pNode->selectNodes(bstr_t(".//ResourceGroupMember/ResourceIdentifier"));
			Cell cell;
			cell.name = resource.name ;
			cell.identifier = resource.identifier;
			for(int j=0; j< members->length; j++)
			{
				MSXML2::IXMLDOMNodePtr pMember = NULL;					
				members->get_item(j, &pMember);
				bstr_t identifier =  (pMember!=NULL) ? pMember->Gettext() : L"None";
				cell.resourceIds.push_back (identifier);
			}
			cells.push_back(cell);
			continue;
		}

		resource.capacity = GetProperty(pNode, bstr_t(L"Capacity"), bstr_t(L"1"));  
		resource.manufacturer = GetProperty(pNode, bstr_t(L"Manufacturer"), bstr_t(L"Acme"));  
		resource.serial_number = GetProperty(pNode, bstr_t(L"SerialNumber"), bstr_t(L"Acme"));  
		// Look for distributions
		properties= pNode->selectNodes(bstr_t(".//Property"));
		for(int j=0; j< properties->length; j++)
		{
			MSXML2::IXMLDOMNodePtr pProp = NULL;					
			properties->get_item(j, &pProp);
			MSXML2::IXMLDOMNodePtr pName = pProp->selectSingleNode(bstr_t(".//Name"));
			bstr_t propName =  (pName!=NULL) ? pName->Gettext() : L"None";
			if(propName==bstr_t(L"None"))
				continue;
			bstr_t parameters[2] = { L"MTBF:Measured", L"MTTR:Measured" };
			for(int k=0; k< sizeof(parameters)/sizeof(bstr_t); k++)
			{
				if(propName == parameters[k])
				{
					Distribution d;
					d.name = propName;
					d.units = GetElement(pProp, bstr_t(L"Unit"), bstr_t(L"Hour"));  
					d.distname = GetElement(pProp, bstr_t(L".//Distribution/Name"), bstr_t(L"None"));  
					d.mappedvalues = GetNameValueProperties(pProp, L".//DistributionParameter")	;	
					if(propName == bstr_t(L"MTBF:Measured"))
						resource.mtbf = d; 
					else if(propName == bstr_t(L"MTTR:Measured"))
						resource.mttr = d; 
				}
			}
		}
		resources.push_back(resource);

	}
	nodes = root->selectNodes(_bstr_t("//DistributionDefinition"));
	for(int j=0; j< nodes->length; j++)
	{
		MSXML2::IXMLDOMNodePtr pProp = NULL;					
		nodes->get_item(j, &pProp);
		bstr_t id = GetElement(pProp,bstr_t(".//Identifier"));
		Distribution d = GetDistribution(pProp);
		Distribution::distributions[id]=d;
	}

	nodes = root->selectNodes(_bstr_t("//DataSection/Job"));
	for(int j=0; j< nodes->length; j++)
	{
		Job job;
		MSXML2::IXMLDOMNodePtr pNode = NULL;					
		nodes->get_item(j, &pNode);
		MSXML2::IXMLDOMNodeListPtr parts = pNode->selectNodes(_bstr_t(".//PlannedEffort/PartsProduced"));
		job.name = GetElement(pNode,"./Identifier");
		for(int k=0; k< parts->length; k++)
		{
			MSXML2::IXMLDOMNodePtr pPart = NULL;					
			parts->get_item(k, &pPart);
			bstr_t id = GetElement(pPart,"./PartType/PartTypeIdentifier");
			job.partIds.push_back(id);
			job.partQuantity.push_back(GetElement(pPart,"PartQuantity"));
		}
		jobs.push_back(job);
	}


	nodes = root->selectNodes(_bstr_t("//DataSection/PartType"));
	for(int j=0; j< nodes->length; j++)
	{
		Part part;
		MSXML2::IXMLDOMNodePtr pProp = NULL;					
		nodes->get_item(j, &pProp);
		MSXML2::IXMLDOMNodePtr pArrivals = pProp->selectSingleNode(bstr_t(".//Property[Name = 'arrivals']"));
		if(pArrivals!=NULL)
		{
			part.arrivals = GetDistribution(pArrivals);
		}

		part.name = GetElement(pProp,bstr_t("./Name"));
		part.identifier = GetElement(pProp,bstr_t("./Identifier"));
		part.processplanidentifier = GetElement(pProp,bstr_t(".//ProcessPlan/ProcessPlanIdentifier"));
		parts.push_back(part);
	}
	// Process plan parsing
	nodes = root->selectNodes(_bstr_t("//DataSection/ProcessPlan"));
	for(int j=0; j< nodes->length; j++)
	{
		ProcessPlan plan;
		MSXML2::IXMLDOMNodePtr pProp = NULL;					
		nodes->get_item(j, &pProp);

		plan.identifier = GetElement(pProp,L"Identifier");
		plan.firstProcessId = GetElement(pProp,L"FirstProcess/ProcessIdentifier");

		//plan.partsProducedId = GetElement(pProp,L"PartsProduced/PartType/PartTypeIdentifier");
		//plan.partsProducedQuantity = GetElement(pProp,L"PartsProduced/PartType/PartQuantity", L"1");
		//plan.partsConsumedId = GetElement(pProp,L"PartsConsumed/PartType/PartTypeIdentifier");
		//plan.partsConsumedQuantity = GetElement(pProp,L"PartsConsumed/PartType/PartQuantity", L"1");
		
		MSXML2::IXMLDOMNodeListPtr  processes = pProp->selectNodes(_bstr_t("./Process"));
		for(int k=0; k< processes->length; k++)
		{
			Process process;
			MSXML2::IXMLDOMNodePtr pProcess = NULL;					
			processes->get_item(k, &pProcess);
			process.identifier = GetElement(pProcess,L"Identifier");

			process.partsProducedId = GetElement(pProcess,L"PartsProduced/PartType/PartTypeIdentifier");
			process.partsProducedQuantity = GetElement(pProcess,L"PartsProduced/PartType/PartQuantity", L"1");
			process.partsConsumedId = GetElement(pProcess,L"PartsConsumed/PartType/PartTypeIdentifier");
			process.partsConsumedQuantity = GetElement(pProcess,L"PartsConsumed/PartType/PartQuantity", L"1");

			process.operationTime.units = GetElement(pProcess,L"OperationTime/Unit", L"Hours");
			process.operationTime.time = GetElement(pProcess,L"OperationTime/Value");
			process.setupTime.units = GetElement(pProcess,L"SetupTime/Unit", L"Hours");
			process.setupTime.time = GetElement(pProcess,L"SetupTime/Value");
			process.scrapPercentage = GetProperty(pProcess, L"ScrapPercentage", "0");
			process.repetitionCount = GetElement(pProcess, L"RepetitionCount", "1");
			//std::vector<bstr_t> resourcesRequired;

			if( pProp->selectSingleNode(bstr_t(".//ResourcesRequired")) !=NULL)
			{
				MSXML2::IXMLDOMNodeListPtr pResourcesRequired=pProcess->selectNodes(bstr_t(".//ResourcesRequired/Resource"));
				for(int m=0; m< pResourcesRequired->length; m++)
				{
					MSXML2::IXMLDOMNodePtr pResource = NULL;					
					pResourcesRequired->get_item(m, &pResource);
					bstr_t resourceid = GetElement(pResource, L"ResourceIdentifier");
					process.resourcesRequired.push_back(resourceid);
				}
			}


			if( pProp->selectSingleNode(bstr_t(".//SubProcessGroup")) !=NULL)
			{
				process.type= GetElement(pProcess, L".//SubProcessGroup/Type", L"sequence");
				MSXML2::IXMLDOMNodeListPtr pSubProcesses=pProcess->selectNodes(bstr_t(".//SubProcessGroup/Process"));
				for(int m=0; m< pSubProcesses->length; m++)
				{
					MSXML2::IXMLDOMNodePtr pProcess = NULL;					
					pSubProcesses->get_item(m, &pProcess);
					bstr_t bstep = GetElement(pProcess, L"ProcessIdentifier");
					process.steps.push_back(bstep);
				}
			}
			plan.processes.push_back(process);

		}

		processplans.push_back(plan);


	}
	

}

Process ProcessPlan::FindProcess(bstr_t name)
{
	Process p;
	for(int i=0; i< this->processes.size(); i++)
	{
		if(processes[i].identifier == name)
			return processes[i];
	}
	return p;
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