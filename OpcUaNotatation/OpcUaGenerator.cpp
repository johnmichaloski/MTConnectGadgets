#include "StdAfx.h"
#include "OpcUaGenerator.h"
#include "StdStringFcn.h"


static _bstr_t checkParseError(MSXML2::IXMLDOMParseErrorPtr pError)
{
	_bstr_t parseError =_bstr_t("At line ")+ _bstr_t(pError->Getline()) + _bstr_t("\n")+ _bstr_t(pError->Getreason());
	MessageBox(NULL,parseError, "Parse Error",MB_OK);
	return parseError;

}

static _bstr_t GetAttribute(MSXML2::IXMLDOMNodePtr node, _bstr_t attribute, _bstr_t defaultVal=L"")
{
	_bstr_t text= defaultVal;
	if(node==NULL)
		return defaultVal;
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
COpcUaGenerator::COpcUaGenerator(void)
{
	if(mapping.size() == 0)
	{
		InitMapping();
		InitUnitMapping();
	}
}

COpcUaGenerator::~COpcUaGenerator(void)
{

}

void COpcUaGenerator::UsedType(std::string name)
{
	_UsedTypes[name]++;
}

bool COpcUaGenerator::IsUnusedType(std::string name)
{ 
	// return false;
	if(_UsedTypes.find(name) == _UsedTypes.end()) 
		return true; 
	return false;
}

void COpcUaGenerator::Close()
{
	m_pSchemaCache=NULL;
	m_pXSDDoc=NULL;
	m_pXMLDoc=NULL;
}
std::vector<AttrType> COpcUaGenerator::GetAttributes(MSXML2::IXMLDOMNodePtr pNode)
{
	std::vector<AttrType> attrs;
	MSXML2::IXMLDOMNodeListPtr pAttrs = pNode->selectNodes(_bstr_t(".//xs:attribute"));
	for(int j=0; j< pAttrs->length; j++)
	{
		MSXML2::IXMLDOMNodePtr pAttr = NULL;	
		pAttrs->get_item(j, &pAttr);
		AttrType attr;
		attr._name=(LPCSTR)GetAttribute(pAttr, "name");
		attr._type=(LPCSTR)GetAttribute(pAttr, "type");
		_UsedTypes[attr._type]++;
		std::string use = (LPCSTR)GetAttribute(pAttr, "use");
		if(use == "required")
			attr._use="Mandatory";
		else
			attr._use="Optional";
		attrs.push_back(attr);
	}
	return attrs;
}


static std::string AttributeValueTable(std::string browsename, std::string truefalseAbstract)
{
	std::string html;
	//html+="<table class=\"gridtable\" style='width:600px'>\n";
	html+="<tr> <th colspan='2' align='left' style='width:100px'> Attribute </th><th colspan='4' align='left' style='width:500px'> Value </th></tr>\n";
	html+="<tr> <td colspan='2' align='left' style='width:100px'> BrowseName </td><td colspan='4' align='left' style='width:500px'>"+ browsename + " </td></tr>\n";
	html+="<tr> <td colspan='2' align='left' style='width:100px'> IsAbstract </td><td colspan='4' align='left' style='width:500px'>"+ truefalseAbstract + "</td></tr>\n";
	//html+="</table>\n";
	return html;
}

static std::string ReferencesTableSetup()
{
	std::string html;
	//html+="<table class=\"gridtable\" style='width:600px'>\n";
	html+="<tr>";
	html+="<th colspan='1' align='left' style='width:100px'> Reference </th>";
	html+="<th colspan='1' align='left' style='width:100px'> NodeClass </th>";
	html+="<th colspan='1' align='left' style='width:100px'>"+  std::string("BrowseName") +"</th>";
	html+="<th colspan='1' align='left' style='width:100px'>"+  std::string("DataType") +"</th>";
	html+="<th colspan='1' align='left' style='width:100px'>"+  std::string("TypeDefinition") +"</th>";
	html+="<th colspan='1' align='left' style='width:100px'>"+  std::string("ModelingRule") +"</th>";
	html+="</tr>";	
	return html;
}

static std::string ANAME(std::string name)
{
	return "<A NAME=\"" + name  + "\">"+ name + "</A>";
}

static std::string AHREF(std::string name)
{
	return "<A HREF=\"#" + name  + "\">"+ name + "</A>";
}
void COpcUaGenerator::Clear()
{
	_SimpleTypes.clear();
	_ComplexTypes.clear();
	_Elements.clear();
	_StringSimpleTypes.clear();
}

void COpcUaGenerator::MarkType(std::string typeName)
{
	if( _ComplexTypes.find(typeName)!= _ComplexTypes.end())
		MarkComplexTypes(typeName);
	else if( _Elements.find(typeName)!= _Elements.end())
		MarkElementTypes(typeName);
	else if( _SimpleTypes.find(typeName)!= _SimpleTypes.end())
		MarkSimpleTypes(typeName);
	else
		_UsedTypes[typeName]++;
}

void COpcUaGenerator::MarkSimpleTypes(std::string typeName)
{
	std::map<std::string, SimpleType>::iterator it =  _SimpleTypes.find(typeName);
	if(it == _SimpleTypes.end())
		return ;

	_UsedTypes[typeName]++;
	if(_UsedTypes[typeName] > 10)
		return;
	SimpleType type =(*it).second;
	_UsedTypes[type._type]++;

	if(	type._enum.size() > 0)
	{
		_UsedTypes[typeName + "Enum"]++;	
	}

	for(int i=0; i< type._union.size(); i++)
	{
		MarkType(type._union[i]);
	}
	
}

void COpcUaGenerator::MarkComplexTypes(std::string typeName)
{
	std::map<std::string, ComplexType>::iterator it =  _ComplexTypes.find(typeName);
	if(it == _ComplexTypes.end())
		return ;

	_UsedTypes[typeName]++;
	if(_UsedTypes[typeName] > 10)
		return;
	ComplexType type =(*it).second;

	for(int i=0; i< type._attr.size(); i++)
	{
		AttrType attr = type._attr[i];
		MarkType(attr._type);
	}
	for(int i=0; i< type._seq.size(); i++)
	{
		ElemType elem = type._seq[i];
		MarkType(elem._type);
	}

	if(!type._baseClass.empty())
		MarkType(type._baseClass);

	if(	type._enum.size() > 0)
	{
		_UsedTypes[typeName + "Enum"]++;	
	}
	
}
void COpcUaGenerator::MarkElementTypes(std::string elementName)
{
	std::map<std::string, ElemType>::iterator it =  _Elements.find(elementName);
	if(it == _Elements.end())
		return ;

	_UsedTypes[elementName]++;
	if(_UsedTypes[elementName] > 10)
		return;

	ElemType elem =(*it).second;
	MarkType(elem._type);
	MarkType(elem._substitutionGroup);
	
}

void COpcUaGenerator::ReadXmlSchema(std::string xmlfilename)
{
	IXMLDOMParseErrorPtr  pError;
	_bstr_t xmlfile = xmlfilename.c_str();

	// load the XML file
	// ****** you need to use IXMLDOMDocument2 interface *********
	HRESULT hr = m_pXMLDoc.CreateInstance(__uuidof(MSXML2::DOMDocument));
	m_pXMLDoc->async =  VARIANT_FALSE; 

	hr = m_pXMLDoc->load(xmlfile);      

	//check on the parser error      
	if(hr!=VARIANT_TRUE)
	{
		checkParseError(m_pXMLDoc->parseError);
	}

	MSXML2::IXMLDOMNodePtr root = m_pXMLDoc->GetdocumentElement();
	MSXML2::IXMLDOMNodeListPtr nodes = root->childNodes; // ->selectNodes(_bstr_t("//DataItem"));

	for(int i=0; i< nodes->length; i++)
	{
		MSXML2::IXMLDOMNodePtr pNode = NULL;	
		nodes->get_item(i, &pNode);
		std::string elemName = (LPCSTR) pNode->baseName;
		std::string name = GetAttribute(pNode, "name");
		OutputDebugString((elemName + " " + name+"\n").c_str());
		std::string doc;
		try{
			MSXML2::IXMLDOMNodePtr pDoc = pNode->selectSingleNode(_bstr_t(".//xs:documentation"));
			doc = (LPCSTR) pDoc->text;
		}
		catch(...)
		{}
		if(elemName=="simpleType")
		{
			SimpleType simpletype;
			MSXML2::IXMLDOMNodePtr pSimpleType=pNode->selectSingleNode(_bstr_t("./xs:restriction"));
			simpletype._name=name;
			simpletype._doc=doc;
			if((pSimpleType!= NULL) &&  GetAttribute(pSimpleType, "base") == _bstr_t("xs:string"))
			{
				MSXML2::IXMLDOMNodeListPtr pEnumTypes=pSimpleType->selectNodes(_bstr_t("./xs:enumeration"));
				if(pEnumTypes!=NULL &&  pEnumTypes->length > 0)
				{
					simpletype._type = "enumeration";
					for(int k=0; k< pEnumTypes->length; k++)
					{
						MSXML2::IXMLDOMNodePtr pEnum = NULL;	
						pEnumTypes->get_item(k, &pEnum);
						simpletype._enum[(LPCSTR) GetAttribute(pEnum, "value")]=ConvertToString(k);
					}
					_SimpleTypes[name] = simpletype;
				}
				else
				{
					simpletype._type = "string";
					_SimpleTypes[name] = simpletype;  // could have patten
				}
			}
			else if(pSimpleType!= NULL)
			{
				simpletype._type = GetAttribute(pSimpleType, "base", "None");
				ReplaceAll(simpletype._type, "xs:", "");
				_SimpleTypes[name] = simpletype;  // could have patten
			}
			else
			{
				pSimpleType=pNode->selectSingleNode(_bstr_t("./xs:union"));
				if(pSimpleType!=NULL)
				{
					std::string memberTypes = GetAttribute(pSimpleType, "memberTypes");
					simpletype._union = TrimmedTokenize(memberTypes, " ");
					std::sort(simpletype._union.begin(), simpletype._union.end());
					simpletype._type == "union";
					_SimpleTypes[name] = simpletype;  // could have patten
				}

			}

		}
		if(elemName=="element")
		{
			ElemType type;
			type._doc = doc;
			type._substitutionGroup = GetAttribute(pNode, "substitutionGroup", L"");
			type._name = GetAttribute(pNode, "name", L"");
			type._type = GetAttribute(pNode, "type", L"");
			_UsedTypes[type._type]++;
			_Elements[name]=type;
		}

		if(elemName=="complexType")
		{
			ComplexType type;
			type._doc = doc;
			type._abstract = GetAttribute(pNode, "abstract", L"false");
			type._attr=GetAttributes(pNode);
			if(name == "SensorConfigurationType")
			{
				DebugBreak();
			}

			MSXML2::IXMLDOMNodePtr pSeq=pNode->selectSingleNode(_bstr_t("./xs:sequence"));
			if(pSeq==NULL)
			{
				pSeq = pNode->selectSingleNode(_bstr_t("./xs:complexContent/xs:extension/xs:sequence"));
			}

			if(pSeq != NULL)
			{
				MSXML2::IXMLDOMNodeListPtr pElems = pSeq->selectNodes(_bstr_t(".//xs:element"));

				for(int j=0; j< pElems->length; j++)
				{
					MSXML2::IXMLDOMNodePtr pElem = NULL;	
					pElems->get_item(j, &pElem);
					ElemType elem;
					elem._name=(LPCSTR)GetAttribute(pElem, "name");
					elem._type=(LPCSTR)GetAttribute(pElem, "type");
					_UsedTypes[elem._type]++;
					elem._minOccurs=(LPCSTR)GetAttribute(pElem, "minOccurs", "0");
					elem._maxOccurs=(LPCSTR)GetAttribute(pElem, "maxOccurs", "0");
					if(elem._type.empty())
					{
						elem._type=(LPCSTR)GetAttribute(pElem, "ref");
						_UsedTypes[elem._type]++;
					}

					MSXML2::IXMLDOMNodePtr pDoc = pElem->selectSingleNode(_bstr_t(".//xs:documentation"));
					if(pDoc) elem._doc = (LPCSTR) pDoc->text;
					type._seq.push_back(elem);
				}
			}
			//if(name == "EventType")
			//{
			//	DebugBreak();
			//	MSXML2::IXMLDOMNodePtr pBaseClass = pNode->selectSingleNode(_bstr_t(".//xs:simpleContent/xs:restriction"));
			//	type._baseClass =  (LPCSTR)GetAttribute(pBaseClass, "base");
			//}

			if(pNode->selectSingleNode(_bstr_t("./xs:complexContent")) != NULL)
			{
				MSXML2::IXMLDOMNodePtr pBaseClass = pNode->selectSingleNode(_bstr_t("./xs:complexContent/xs:extension"));
				type._baseClass =  (LPCSTR)GetAttribute(pBaseClass, "base");
			}
			if(pNode->selectSingleNode(_bstr_t("./xs:simpleContent")) != NULL)
			{
				MSXML2::IXMLDOMNodePtr pBaseClass = pNode->selectSingleNode(_bstr_t("./xs:simpleContent/xs:extension"));
				type._baseClass =  (LPCSTR)GetAttribute(pBaseClass, "base");
			}

			if(pNode->selectSingleNode(_bstr_t("./xs:simpleContent/xs:restriction")) != NULL)
			{
				MSXML2::IXMLDOMNodePtr pBaseClass = pNode->selectSingleNode(_bstr_t("./xs:simpleContent/xs:restriction"));
				type._baseClass =  (LPCSTR)GetAttribute(pBaseClass, "base");

				MSXML2::IXMLDOMNodeListPtr pEnumTypes=pBaseClass->selectNodes(_bstr_t("./xs:enumeration"));
				if(pEnumTypes!=NULL &&  pEnumTypes->length > 0)
				{
					for(int k=0; k< pEnumTypes->length; k++)
					{
						MSXML2::IXMLDOMNodePtr pEnum = NULL;	
						pEnumTypes->get_item(k, &pEnum);
						type._enum[(LPCSTR) GetAttribute(pEnum, "value")]=ConvertToString(k);
					}
				}
			}
			_ComplexTypes[name]=type;
		}
	}
	for(std::map<std::string, int>::iterator it = _UsedTypes.begin(); it!=_UsedTypes.end(); it++)
	{
		OutputDebugString(((*it).first+ "=" + ConvertToString((*it).second) + "\n").c_str());
	}

}
void COpcUaGenerator::AddConditions()
{
	static std::string sConditions = "ACCELERATION, ACCUMULATED_TIME, ACTUATOR, AMPERAGE, ANGLE, ANGULAR-ACCELERATION, ANGULAR_VELOCITY, COMMUNICATIONS, CONCENTRATION, CONDUCTIVITY, DATA_RANGE, DIRECTION , DISPLACEMENT, ELECTRICAL_ENERGY, FILL_LEVEL, FLOW, FREQUECNCY, HARDWARE, LEVEL, LINEAR_FORCE, LOAD, LOGIC_PROGRAM, MASS, MOTION_PROGRAM, PATH_FEEDRATE, PATH_POSITION, PH, POSITION, POWER_FACTOR, PRESSURE, RESISTANCE, ROTARY_VELOCITY, SOUND_LEVEL, SPINDLE_SPEED, STRAIN, SYSTEM, TEMPERATURE, TILT, TORQUE, VOLT_AMPERAGE, VOLT_AMPERAGE_REACTIVE, VELOCITY, VISCOSITY, VOLTAGE, WATTAGE";
	std::vector<std::string> conditions = TrimmedTokenize(sConditions,",");
	for(int i=0; i< conditions.size(); i++)
	{
		ElemType type;
		type._name =conditions[i];
		type._type ="ConditionType";
		type._substitutionGroup = "Condition";
		_UsedTypes["ConditionType"]++;
		_Elements[conditions[i]]=type;
	}
	ElemType type;
	type._name ="Header";
	type._type ="HeaderType";
	_UsedTypes["HeaderType"]++;
	_Elements[type._name]=type;

	
}

std::string COpcUaGenerator::GenerateStreamsDocument(std::string xmloutputfilename)
{
	//////////////////////////////////////////////////////
	std::string html;
	html+="<html>\n";
	html+="<STYLE>" +  HtmlStyle();
	html += "</STYLE>"; 

	html+="<body>\n";
	int i=1;

	if(_bSampleTypes)
	{
		html+="<h2> Sample Types mapped into OPC UA float with engineering units</h2>\n";
		html+="The following table lists the MTConnect Complex types that are mapped into OPC UA float type with engineering units.";
		html+="<table class=\"gridtable\" style='width:600px'>\n";
		html+="<tr><th colspan='2' align='left' style='width:200px'> Sample </th>";
		html+="<th colspan='2' align='left' style='width:200px'> MTConnect Units </th>";
		html+="<th colspan='2' align='left' style='width:200px'> OPC UA Engineering Units </th></tr>";
		for(std::map<std::string, ComplexType>::iterator it= _ComplexTypes.begin(); it!=_ComplexTypes.end(); it++, i++)
		{
			ComplexType type = (*it).second;
			std::string subtype = (*it).second._baseClass ;

			if((*it).second._doc.find("DEPRECATED") != std::string::npos)
				continue;

			if(subtype == "SampleType")
			{
				html+="<tr><td colspan='2' align='left' style='width:200px'>"+ ANAME((*it).first) +"</td>";
				html+="<td colspan='2' align='left' style='width:200px'>"+ unitmapping[(*it).first] +"</td>";
				html+="<td colspan='2' align='left' style='width:200px'></td></tr>";
			}
		}
		html+="</table>\n";
	}

	html+="<h2> Simple Types</h2>\n";
	for(std::map<std::string, SimpleType>::iterator it= _SimpleTypes.begin(); it!=_SimpleTypes.end(); it++, i++)
	{
		SimpleType simpletype = (*it).second;
		std::string subtype = (*it).second._type ;
		if((*it).second._doc.find("DEPRECATED") != std::string::npos)
			continue;
		if(IsUnusedType((*it).first))
			continue;

		std::string name = (*it).first;
#if 0
		name=ReplaceOnce(name,"Value","");
		if(_ComplexTypes.find(name) != _ComplexTypes.end())
			continue;
#endif
		html+="<h3>"+ ANAME((*it).first) + "</h3>\n";
		if(simpletype._type == "enumeration")
		{
			html+=GenerateEnumeration(simpletype._name, simpletype._enum); 

		}

		// Documentated annotations
		html+="<p>" + (*it).second._doc + "</p>\n";

		html+="<table class=\"gridtable\" style='width:600px'>\n";
		html+=AttributeValueTable((*it).first, "false");
		html+=ReferencesTableSetup();

		if(simpletype._union.size()>0)
		{
			for(int k=0; k<simpletype._union.size(); k++) 
				html+="<tr> <td colspan='6' align='left' style='width:600px'> Union of "+ simpletype._union[k]   + "</td></tr>\n";
		}
		else
			html+="<tr> <td colspan='6' align='left' style='width:600px'> Subtype of "+ subtype   + "</td></tr>\n";
		html+="</table>\n";
	}

	html+="<BR>\n";
	html+="<h2> Complex Types</h2>\n";
	for(std::map<std::string, ComplexType>::iterator it= _ComplexTypes.begin(); it!=_ComplexTypes.end(); it++)
	{
		ComplexType type = (*it).second;
		std::string name = (*it).first;

		if(_bSampleTypes && type._baseClass == "SampleType")
			continue;
		if(type._doc.find("DEPRECATED") != std::string::npos)
			continue;

		// Check if unused type, if so remove.
		if(IsUnusedType((*it).first))
			continue;

		if(type._baseClass == "ConditionType")
			continue;

		if((*it).first.find("TimeSeries") != std::string::npos)
			continue;

		if(type._baseClass == "InterfaceType")
			continue;
		if(name=="InterfaceType" || name == "InterfacesType")
			continue;

		html+="<h3>"+ ANAME( name) + "</h3>\n";
		if(type._enum.size() > 0)
			html+=GenerateEnumeration(name, type._enum);

		html+="<p>" + type._doc + "</p>\n";
		html+="<table class=\"gridtable\" style='width:600px'>\n";
		html+=AttributeValueTable(name, type._abstract);

		html+=ReferencesTableSetup();

		if(! type._baseClass.empty())
		{
			html+="<tr> <td  colspan='6' align='left' style='width:600px'> Inherit the children of the "+ AHREF( (*it).second._baseClass )  + "</td></tr>\n";
		}

		if(type._enum.size() > 0)
		{
			html+="<tr> <td  colspan='6' align='left' style='width:600px'> Restrict values to "+ AHREF( (*it).first + "Enum") + "</td></tr>\n";
		}
		for(int i=0; i< type._attr.size(); i++)
		{
			AttrType attr = type._attr[i];
			if(attr._name == "name")
				continue;
			if(attr._name == "dataItemId")
				continue;
			if(attr._name == "id")
				continue;
			html+="<tr>";
			html+="<td  colspan='1' align='left' style='width:100px'> HasProperty </td>";
			html+="<td colspan='1' align='left' style='width:100px'> Variable </td>";
			html+="<td colspan='1' align='left' style='width:100px'>"+  attr._name +"</td>";
			html+="<td colspan='1' align='left' style='width:100px'>"+  AHREF(attr._type) +"</td>";
			html+="<td colspan='1' align='left' style='width:100px'>"+  std::string("ProperyType") +"</td>";
			html+="<td colspan='1' align='left' style='width:100px'>"+  attr._use +"</td>";
			html+="</tr>";
		}

		for(int i=0; i< type._seq.size(); i++)
		{
			ElemType elem = type._seq[i];
			html+="<tr>";
			html+="<td colspan='1' align='left' style='width:100px'> HasComponent </td>";
			html+="<td colspan='1' align='left' style='width:100px'> Object </td>";
			html+="<td colspan='1' align='left' style='width:100px'>"+  elem._name +"</td>";
			html+="<td colspan='1' align='left' style='width:100px'>"+ AHREF( elem._type) +"</td>";
			if(ConvertString<int>(elem._minOccurs,-1) == 0)
			{
				html+="<td colspan='1' align='left' style='width:100px'>"+  std::string("FolderType") +"</td>";
				html +="<td colspan='1' align='left' style='width:100px'>Optional(" + elem._minOccurs + ".." + elem._maxOccurs + ")</tr>";
			}
			else if(ConvertString<int>(elem._minOccurs,0) == 1)
			{
				html+="<td colspan='1' align='left' style='width:100px'>"+  std::string("FolderType") +"</td>";
				html +="<td colspan='1' align='left' style='width:100px'>Mandatory(" + elem._minOccurs + ".." + elem._maxOccurs + ")</tr>";
			}
			else if(elem._maxOccurs == "unbounded")
			{
				html+="<td colspan='1' align='left' style='width:100px'>"+  std::string("FolderType") +"</td>";
				html +="<td colspan='1' align='left' style='width:100px'>OptionalPlaceholder(" + elem._minOccurs + ".." + elem._maxOccurs + ")</tr>";
			}
			else
			{
				//html+="<td align='left' style='width:100px'>"+  std::string("FolderType") +"</td>";
				//html +="<td align='left' style='width:100px'>Optional(" + elem._minOccurs + ".." + elem._maxOccurs + ")</tr>";
			}
		}


		html+="</table>\n";
		html+="<BR>\n";
	}

	html+="<h2> OPC UA Variable Types</h2>\n";
	html+="<h3> Abstract Variable Types</h3>\n";
	html+=GenerateElement(_Elements["Result"]);
	html+=GenerateElement(_Elements["Header"]);
	html+=GenerateElement(_Elements["MTConnectStreams"]);

	html+="<h3> Sample Variable Types</h3>\n";
	html+="Samples are point-in-time readings from a component reporting what the value is at that instant.\n";  
	for(std::map<std::string, ElemType>::iterator it= _Elements.begin(); it!=_Elements.end(); it++, i++)
	{
		if((*it).second._doc.find("DEPRECATED") != std::string::npos )
			continue;			

		ElemType elemtype = (*it).second;
		if(elemtype._substitutionGroup == "Sample" || (*it).first  == "Sample")
			html+=GenerateElement(elemtype);
	}

	html+="<h3> Event Variable Types</h3>\n";
	html+="An Event changes state to a limited set of values or represents a message. It is assumed that an event remains at a state until the next event occurs; it cannot have any intermediate values between the reported values.  \n";
	for(std::map<std::string, ElemType>::iterator it= _Elements.begin(); it!=_Elements.end(); it++, i++)
	{
		if((*it).second._doc.find("DEPRECATED") != std::string::npos)
			continue;			

		ElemType elemtype = (*it).second;
		if(elemtype._substitutionGroup == "Event" || (*it).first  == "Event")
			html+=GenerateElement(elemtype);
	}
	html+="<h3> Condition Variable Types</h3>\n";
	html+="A Condition communicates the device’s health and ability to function.  It can be one of Unavailable, Normal, Warning, or Fault and there can be multiple active conditions at one time; whereas a sample or event can only have a single value at one point in time.\n";
	for(std::map<std::string, ElemType>::iterator it= _Elements.begin(); it!=_Elements.end(); it++, i++)
	{
		if((*it).second._doc.find("DEPRECATED") != std::string::npos)
			continue;			

		ElemType elemtype = (*it).second;
		if(elemtype._name == "Normal" || elemtype._name == "Warning" || elemtype._name == "Fault" || elemtype._name == "Unavailable")
			continue;
		if(elemtype._substitutionGroup == "Condition")
			html+=GenerateElement(elemtype);
	}

	html+="</body></html>\n";
	return html;

}

std::string COpcUaGenerator::GenerateAssetsDocument()
{
	//////////////////////////////////////////////////////
	std::string html;
	html+="<html>\n";
	html+="<STYLE>" +  HtmlStyle();
	html += "</STYLE>"; 

	html+="<body>\n";
	int i=1;

	html+="<h2> Simple Types</h2>\n";
	for(std::map<std::string, SimpleType>::iterator it= _SimpleTypes.begin(); it!=_SimpleTypes.end(); it++, i++)
	{
		SimpleType simpletype = (*it).second;
		std::string subtype = (*it).second._type ;
		if((*it).second._doc.find("DEPRECATED") != std::string::npos)
			continue;

		std::string name = (*it).first;
#if 0
		name=ReplaceOnce(name,"Value","");
		if(_ComplexTypes.find(name) != _ComplexTypes.end())
			continue;
#endif
		html+="<h3>"+ ANAME((*it).first) + "</h3>\n";
		if(simpletype._type == "enumeration")
		{
			html+=GenerateEnumeration(simpletype._name, simpletype._enum); 

		}

		// Documentated annotations
		html+="<p>" + (*it).second._doc + "</p>\n";

		html+="<table class=\"gridtable\" style='width:600px'>\n";
		html+=AttributeValueTable((*it).first, "false");
		html+=ReferencesTableSetup();

		if(simpletype._union.size()>0)
		{
			for(int k=0; k<simpletype._union.size(); k++) 
				html+="<tr> <td colspan='6' align='left' style='width:600px'> Union of "+ simpletype._union[k]   + "</td></tr>\n";
		}
		else
			html+="<tr> <td colspan='6' align='left' style='width:600px'> Subtype of "+ subtype   + "</td></tr>\n";
		html+="</table>\n";
	}

	html+="<BR>\n";
	html+="<h2> Complex Types</h2>\n";
	for(std::map<std::string, ComplexType>::iterator it= _ComplexTypes.begin(); it!=_ComplexTypes.end(); it++)
	{
		ComplexType type = (*it).second;
		std::string name = (*it).first;

		//if(_bSampleTypes && type._baseClass == "SampleType")
		//	continue;
		if(type._doc.find("DEPRECATED") != std::string::npos)
			continue;
		if(type._baseClass == "InterfaceType")
			continue;
		if(type._baseClass == "ConditionType")
			continue;
		if((*it).first.find("TimeSeries") != std::string::npos)
			continue;
		if(name=="InterfaceType" || name == "InterfacesType")
			continue;

		html+="<h3>"+ ANAME( name) + "</h3>\n";
		if(type._enum.size() > 0)
			html+=GenerateEnumeration(name, type._enum);

		html+="<p>" + type._doc + "</p>\n";
		html+="<table class=\"gridtable\" style='width:600px'>\n";
		html+=AttributeValueTable(name, type._abstract);

		html+=ReferencesTableSetup();

		if(! type._baseClass.empty())
		{
			html+="<tr> <td  colspan='6' align='left' style='width:600px'> Inherit the children of the "+ AHREF( (*it).second._baseClass )  + "</td></tr>\n";
		}

		if(type._enum.size() > 0)
		{
			html+="<tr> <td  colspan='6' align='left' style='width:600px'> Restrict values to "+ AHREF( (*it).first + "Enum") + "</td></tr>\n";
		}
		for(int i=0; i< type._attr.size(); i++)
		{
			AttrType attr = type._attr[i];
			if(attr._name == "name")
				continue;
			if(attr._name == "dataItemId")
				continue;
			if(attr._name == "id")
				continue;
			html+="<tr>";
			html+="<td  colspan='1' align='left' style='width:100px'> HasProperty </td>";
			html+="<td colspan='1' align='left' style='width:100px'> Variable </td>";
			html+="<td colspan='1' align='left' style='width:100px'>"+  attr._name +"</td>";
			html+="<td colspan='1' align='left' style='width:100px'>"+  AHREF(attr._type) +"</td>";
			html+="<td colspan='1' align='left' style='width:100px'>"+  std::string("ProperyType") +"</td>";
			html+="<td colspan='1' align='left' style='width:100px'>"+  attr._use +"</td>";
			html+="</tr>";
		}

		for(int i=0; i< type._seq.size(); i++)
		{
			ElemType elem = type._seq[i];
			html+="<tr>";
			html+="<td colspan='1' align='left' style='width:100px'> HasComponent </td>";
			html+="<td colspan='1' align='left' style='width:100px'> Object </td>";
			html+="<td colspan='1' align='left' style='width:100px'>"+  elem._name +"</td>";
			html+="<td colspan='1' align='left' style='width:100px'>"+ AHREF( elem._type) +"</td>";
			if(ConvertString<int>(elem._minOccurs,-1) == 0)
			{
				html+="<td colspan='1' align='left' style='width:100px'>"+  std::string("FolderType") +"</td>";
				html +="<td colspan='1' align='left' style='width:100px'>Optional(" + elem._minOccurs + ".." + elem._maxOccurs + ")</tr>";
			}
			else if(ConvertString<int>(elem._minOccurs,0) == 1)
			{
				html+="<td colspan='1' align='left' style='width:100px'>"+  std::string("FolderType") +"</td>";
				html +="<td colspan='1' align='left' style='width:100px'>Mandatory(" + elem._minOccurs + ".." + elem._maxOccurs + ")</tr>";
			}
			else if(elem._maxOccurs == "unbounded")
			{
				html+="<td colspan='1' align='left' style='width:100px'>"+  std::string("FolderType") +"</td>";
				html +="<td colspan='1' align='left' style='width:100px'>OptionalPlaceholder(" + elem._minOccurs + ".." + elem._maxOccurs + ")</tr>";
			}
			else
			{
				//html+="<td align='left' style='width:100px'>"+  std::string("FolderType") +"</td>";
				//html +="<td align='left' style='width:100px'>Optional(" + elem._minOccurs + ".." + elem._maxOccurs + ")</tr>";
			}
		}


		html+="</table>\n";
		html+="<BR>\n";
	}

	html+="<h2> OPC UA Variable Types</h2>\n";
	for(std::map<std::string, ElemType>::iterator it= _Elements.begin(); it!=_Elements.end(); it++, i++)
	{
		html+=GenerateElement((*it).second);
	}
	html+="</body></html>\n";
	return html;

}

std::string COpcUaGenerator::GenerateSensorsDocument()
{
	//////////////////////////////////////////////////////
	std::string html="<html>\n<STYLE>\n" +  HtmlStyle() + "</STYLE>\n<body>\n";
	int i=0;
	html+="<h2> Simple Types</h2>\n";
	for(std::map<std::string, SimpleType>::iterator it= _SimpleTypes.begin(); it!=_SimpleTypes.end(); it++, i++)
	{
		SimpleType simpletype = (*it).second;
		std::string subtype = (*it).second._type ;
		if((*it).second._doc.find("DEPRECATED") != std::string::npos)
			continue;
		if(IsUnusedType((*it).first))
			continue;

		std::string name = (*it).first;
#if 0
		name=ReplaceOnce(name,"Value","");
		if(_ComplexTypes.find(name) != _ComplexTypes.end())
			continue;
#endif
		html+="<h3>"+ ANAME((*it).first) + "</h3>\n";
		if(simpletype._type == "enumeration")
		{
			html+=GenerateEnumeration(simpletype._name, simpletype._enum); 

		}

		// Documentated annotations
		html+="<p>" + (*it).second._doc + "</p>\n";

		html+="<table class=\"gridtable\" style='width:600px'>\n";
		html+=AttributeValueTable((*it).first, "false");
		html+=ReferencesTableSetup();

		if(simpletype._union.size()>0)
		{
			for(int k=0; k<simpletype._union.size(); k++) 
				html+="<tr> <td colspan='6' align='left' style='width:600px'> Union of "+ simpletype._union[k]   + "</td></tr>\n";
		}
		else
			html+="<tr> <td colspan='6' align='left' style='width:600px'> Subtype of "+ subtype   + "</td></tr>\n";
		html+="</table>\n";
	}

	html+="<BR>\n";
	html+="<h2> Complex Types</h2>\n";
	for(std::map<std::string, ComplexType>::iterator it= _ComplexTypes.begin(); it!=_ComplexTypes.end(); it++)
	{
		ComplexType type = (*it).second;
		std::string name = (*it).first;

		if(_bSampleTypes && type._baseClass == "SampleType")
			continue;
		if(type._doc.find("DEPRECATED") != std::string::npos)
			continue;

		// Check if unused type, if so remove.
		if(IsUnusedType((*it).first))
			continue;

		if(type._baseClass == "ConditionType")
			continue;

		if((*it).first.find("TimeSeries") != std::string::npos)
			continue;

		if(type._baseClass == "InterfaceType")
			continue;
		if(name=="InterfaceType" || name == "InterfacesType")
			continue;

		html+="<h3>"+ ANAME( name) + "</h3>\n";
		if(type._enum.size() > 0)
			html+=GenerateEnumeration(name, type._enum);

		html+="<p>" + type._doc + "</p>\n";
		html+="<table class=\"gridtable\" style='width:600px'>\n";
		html+=AttributeValueTable(name, type._abstract);

		html+=ReferencesTableSetup();

		if(! type._baseClass.empty())
		{
			html+="<tr> <td  colspan='6' align='left' style='width:600px'> Inherit the children of the "+ AHREF( (*it).second._baseClass )  + "</td></tr>\n";
		}

		if(type._enum.size() > 0)
		{
			html+="<tr> <td  colspan='6' align='left' style='width:600px'> Restrict values to "+ AHREF( (*it).first + "Enum") + "</td></tr>\n";
		}
		for(int i=0; i< type._attr.size(); i++)
		{
			AttrType attr = type._attr[i];
			if(attr._name == "name")
				continue;
			if(attr._name == "dataItemId")
				continue;
			if(attr._name == "id")
				continue;
			html+="<tr>";
			html+="<td  colspan='1' align='left' style='width:100px'> HasProperty </td>";
			html+="<td colspan='1' align='left' style='width:100px'> Variable </td>";
			html+="<td colspan='1' align='left' style='width:100px'>"+  attr._name +"</td>";
			html+="<td colspan='1' align='left' style='width:100px'>"+  AHREF(attr._type) +"</td>";
			html+="<td colspan='1' align='left' style='width:100px'>"+  std::string("ProperyType") +"</td>";
			html+="<td colspan='1' align='left' style='width:100px'>"+  attr._use +"</td>";
			html+="</tr>";
		}

		for(int i=0; i< type._seq.size(); i++)
		{
			ElemType elem = type._seq[i];
			html+="<tr>";
			html+="<td colspan='1' align='left' style='width:100px'> HasComponent </td>";
			html+="<td colspan='1' align='left' style='width:100px'> Object </td>";
			html+="<td colspan='1' align='left' style='width:100px'>"+  elem._name +"</td>";
			html+="<td colspan='1' align='left' style='width:100px'>"+ AHREF( elem._type) +"</td>";
			if(ConvertString<int>(elem._minOccurs,-1) == 0)
			{
				html+="<td colspan='1' align='left' style='width:100px'>"+  std::string("FolderType") +"</td>";
				html +="<td colspan='1' align='left' style='width:100px'>Optional(" + elem._minOccurs + ".." + elem._maxOccurs + ")</tr>";
			}
			else if(ConvertString<int>(elem._minOccurs,0) == 1)
			{
				html+="<td colspan='1' align='left' style='width:100px'>"+  std::string("FolderType") +"</td>";
				html +="<td colspan='1' align='left' style='width:100px'>Mandatory(" + elem._minOccurs + ".." + elem._maxOccurs + ")</tr>";
			}
			else if(elem._maxOccurs == "unbounded")
			{
				html+="<td colspan='1' align='left' style='width:100px'>"+  std::string("FolderType") +"</td>";
				html +="<td colspan='1' align='left' style='width:100px'>OptionalPlaceholder(" + elem._minOccurs + ".." + elem._maxOccurs + ")</tr>";
			}
			else
			{
				//html+="<td align='left' style='width:100px'>"+  std::string("FolderType") +"</td>";
				//html +="<td align='left' style='width:100px'>Optional(" + elem._minOccurs + ".." + elem._maxOccurs + ")</tr>";
			}
		}


		html+="</table>\n";
		html+="<BR>\n";
	}

	html+="<h2> OPC UA Sensor Variable Types</h2>\n";
	for(std::map<std::string, ElemType>::iterator it= _Elements.begin(); it!=_Elements.end(); it++, i++)
	{
		// Check if unused type, if so remove.
		if(IsUnusedType((*it).first))
			continue;
		html+=GenerateElement((*it).second);
	}
	html+="</body></html>\n";
	return html;
}

std::string COpcUaGenerator::GenerateEnumeration(std::string name, std::map<std::string, std::string> & enums)
{
	std::string html;
	html+="<p>Enumeration: " + ANAME(name + "Enum") + "</p>\n";

	html+="<table class=\"gridtable\" style='width:600px'>\n";

	html+="<tr><th colspan='2' align='left' style='width:200px'> Enum </th>";
	html+="<th colspan='4' align='left' style='width:400px'> Description </th></tr>";
	int n=1;
	for(std::map<std::string, std::string>::iterator it =  enums.begin();
		it!=enums.end(); it++, n++) 
	{
		html+="<tr><td colspan='2' align='left' style='width:200px'>" +  (*it).first + "_" + ConvertToString(n) +"</td>";
		html+="<td colspan='4' align='left' style='width:400px'>" + mapping[(*it).first] + "</td></tr>";
	}

	html+="</table><BR>\n";
	return html;
}
std::string COpcUaGenerator::GenerateElement(ElemType &elemtype)
{
	std::string html;
	std::string subtype = elemtype._type ;
	html+="<h3>"+ ANAME(elemtype._name ) + "</h3>\n";
	html+=elemtype._doc;

	html+="<table class=\"gridtable\" style='width:600px'>\n";
	html+=AttributeValueTable(elemtype._name, "false");
	html+=ReferencesTableSetup();
	if(!elemtype._substitutionGroup.empty())
		html+="<tr> <td  colspan='6' align='left' style='width:600px'> Is a substitute "+ AHREF(elemtype._substitutionGroup)   + "</td></tr>\n";
	if(!elemtype._type.empty())
		html+="<tr> <td  colspan='6' align='left' style='width:600px'> Is a type "+ AHREF(elemtype._type)   + "</td></tr>\n";
	html+="</table>\n";

	return html;

}
std::string COpcUaGenerator::HtmlStyle()
{
	std::string style;
	style+= "P\n";
	style+= "{\n";
	//style+= "	text-indent:10px;\n";
	style+= "	FONT-FAMILY: ""Myriad"", sans-serif;\n";
	style+= "	LINE-HEIGHT: 12pt;\n";
	style+= "	MARGIN-BOTTOM: 0px;\n";
	style+= "	MARGIN-LEFT: 10px;\n";
	style+= "	MARGIN-TOP: 10px\n";
	style+= "}\n";

	//style+= "body\n";
	//style+= "{\n";
	//style+= "	text-indent:20px;\n";
	//style+= "	FONT-FAMILY: ""Myriad"", sans-serif;\n";
	//style+= "	LINE-HEIGHT: 12pt;\n";
	//style+= "	MARGIN-BOTTOM: 0px;\n";
	//style+= "	MARGIN-LEFT: 10px;\n";
	//style+= "	MARGIN-TOP: 10px\n";
	//style+= "}\n";
	//style+= "input.btn {   color:#050;   font: bold 84% 'trebuchet ms',helvetica,sans-serif;   background-color:#fed;   border: 1px solid;   border-color: #696 #363 #363 #696;   filter:progid:DXImageTransform.Microsoft.Gradient   (GradientType=0,StartColorStr='#ffffffff',EndColorStr='#ffeeddaa'); } \n";
	//style+= "input.btnhov {   border-color: #c63 #930 #930 #c63; <input type=\"button\" value=\"Submit\" class=\"bt\n\"   onmouseover=\"this.className='btn btnhov'\" onmouseout=\"this.className='btn'\"/> }\n";
	//style+= "p.small\n";
	//style+= "{	\n";
	//style+= "line-height: 10px\n";
	//style+= "}\n";
	//style+= "p.big\n";
	//style+= "{\n";
	//style+= "line-height: 20px\n";
	//style+= "}\n";
	style+= "H1\n";
	style+= "{\n";
	style+= "	BACKGROUND-COLOR: #003366;\n";
	style+= "	BORDER-BOTTOM: #336699 6px solid;\n";
	style+= "	COLOR: #ffffff;\n";
	style+= "	FONT-SIZE: 130%;\n";
	style+= "	FONT-WEIGHT: normal;\n";
	style+= "	MARGIN: 0em 0em 0em -20px;\n";
	style+= "	PADDING-BOTTOM: 8px;\n";
	style+= "	PADDING-LEFT: 30px;\n";
	style+= "	PADDING-TOP: 16px\n";
	style+= "}\n";

	//style+= "	h1.numbered {n";
	//   style+= "	counter-reset: mynum-h2;n";
	//style+= "	}n";
	//style+= "	h2.numbered {n";
	//   style+= "	counter-reset: mynum-h3;n";
	//style+= "	}n";

	style+= "table.gridtable {\n";
	//style+= " 	BACKGROUND-COLOR: #f0f0e0;\n";
	style+= "	BORDER-COLLAPSE: collapse;\n";
	style+= "	BORDER: #000000 1px solid;\n";
	//style+= "	BORDER-BOTTOM: #ffffff 1px solid;\n";
	//style+= "	BORDER-LEFT: #ffffff 1px solid;\n";
	//style+= "	BORDER-RIGHT: #ffffff 1px solid;\n";
	//style+= "	BORDER-TOP: #ffffff 1px solid;\n";
	style+= "	FONT-SIZE: 10pt;\n";
	style+= "	MARGIN-LEFT: 10px\n";
	style+= "  }\n";

	style+= "table.gridtable td {\n";
	//style+= "	BACKGROUND-COLOR: #e7e7ce;\n";
	style+= "	BORDER: #000000 1px solid;\n";
	//style+= "	BORDER-BOTTOM: #0 1px solid;\n";
	//style+= "	BORDER-LEFT: #0 1px solid;\n";
	//style+= "	BORDER-RIGHT: #0 1px solid;\n";
	//style+= "	BORDER-TOP: #0 1px solid;\n";
	style+= "	PADDING-LEFT: 3px\n";
	style+= "  }\n";
	style+= "table.gridtable th {\n";
	style+= "	BORDER: #000000 1px solid;\n";
	//style+= "	BACKGROUND-COLOR: #cecf9c;\n";
	//style+= "	BORDER-BOTTOM: #0 1px solid;\n";
	//style+= "	BORDER-LEFT: #0 1px solid;\n";
	//style+= "	BORDER-RIGHT: #0 1px solid;\n";
	//style+= "	BORDER-TOP: #0 1px solid;\n";
	//style+= "	COLOR: #000000;\n";
	style+= "	FONT-WEIGHT: bold\n";
	style+= "  }\n";

	style+= "table.histogram {\n";
	style+= " 	BACKGROUND-COLOR: #f0f0e0;\n";
	style+= "	border-width: 0px;\n";
	style+= "	BORDER-COLLAPSE: collapse;\n";
	style+= "	padding: 0px;\n";
	//style+= "	FONT-SIZE: 70%;\n";
	style+= "	FONT-SIZE: 9pt;\n";
	style+= "	MARGIN-LEFT: 0px\n";
	style+= "  }\n";
	style+= "table.histogram td {\n";
	style+= "	BORDER-BOTTOM: #ffffff 0px solid;\n";
	style+= "	BORDER-LEFT: #ffffff 0px solid;\n";
	style+= "	BORDER-RIGHT: #ffffff 0px solid;\n";
	style+= "	BORDER-TOP: #ffffff 0px solid;\n";
	style+= "	PADDING: 0px\n";
	style+= "	margin: 0px\n";
	style+= "  }\n";

	style+= "table.MsoNormalTable\n";
	style+= "{line-height:115%;\n";
	style+= "font-size:11.0pt;\n";
	style+= "font-family:\"Calibri\",\"sans-serif\";\n";
	style+= "}\n";
	style+= "p.TableNormalParagraph\n";
	style+= "{margin-top:6.0pt;\n";
	style+= "margin-right:0in;\n";
	style+= "margin-bottom:10.0pt;\n";
	style+= "margin-left:0in;\n";
	style+= "line-height:115%;\n";
	style+= "font-size:12.0pt;\n";
	style+= "font-family:\"Calibri\",\"sans-serif\";\n";
	style+= "color:black;\n";
	style+= "}\n";
	return style;
}

std::map<std::string, std::string> COpcUaGenerator::mapping;
void COpcUaGenerator::InitMapping()
{
	mapping.clear();
	mapping["ACCELERATION"] = "Rate of Change of Velocity";
	mapping["ACCUMULATED_TIME"] = "The measurement of accumulated time associated with a component";
	mapping["ACTUATOR"] = "An actuator related condition.";
	mapping["AMPERAGE"] = "A high or low condition for the electrical current.";
	mapping["ANGLE"] = "The angular position of a component relative to the parent.";
	mapping["ANGULAR-ACCELERATION"] = "Rate of change of angular velocity.";
	mapping["ANGULAR_VELOCITY"] = "Rate of change of angular position";
	mapping["COMMUNICATIONS"] = "A communications failure indicator.";
	mapping["CONCENTRATION"] = "Percentage of one component within a mixture of components";
	mapping["CONDUCTIVITY"] = "The ability of a material to conduct electricity";
	mapping["DATA_RANGE"] = "Information provided is outside of expected value range";
	mapping["DIRECTION "] = "The direction of motion of a component";
	mapping["DISPLACEMENT"] = "The change in position of an object";
	mapping["ELECTRICAL_ENERGY"] = "The measurement of electrical energy consumption by a component";
	mapping["FILL_LEVEL"] = "Represents the amount of a substance remaining compared to the planned maximum amount of that substance";
	mapping["FLOW"] = "The rate of flow of a fluid ";
	mapping["FREQUENCY"] = "The number of occurrences of a repeating event per unit time";
	mapping["HARDWARE"] = "The hardware subsystem of the component operation condition.";
	mapping["LEVEL"] = "DEPRECATED in Rel 1.2.   See FILL_LEVEL";
	mapping["LINEAR_FORCE"] = "The measure of the push or pull introduced by an actuator or exerted by an object";
	mapping["LOAD"] = "The measure of the percentage of the standard rating of a device";
	mapping["LOGIC_PROGRAM"] = "An error occurred in the logic program or PLC (programmable logic controller).";
	mapping["MASS"] = "The measurement of the mass of an object(s) or an amount of material";
	mapping["MOTION_PROGRAM"] = "An error occurred in the motion program.";
	mapping["PATH_FEEDRATE"] = "The federate of the tool path";
	mapping["PATH_POSITION"] = "The current control point of the path";
	mapping["PH"] = "The measure of acidity or alkalinity ";
	mapping["POSITION"] = "The position of a component.";
	mapping["POWER_FACTOR"] = "The ratio of real power flowing to a load to the apparent power in that AC circuit.";
	mapping["PRESSURE"] = "The measurement of the force per unit area exerted by a gas or liquid.";
	mapping["RESISTANCE"] = "The measurement of the degree to which an object opposes an electric current through it";
	mapping["ROTARY_VELOCITY"] = "The rotational speed of a rotary axis";
	mapping["SOUND_LEVEL"] = "The measurement of sound pressure level";
	mapping["SPINDLE_SPEED"] = "DEPRECATED in Rel 1.2.   See ROTARY_VELOCITY";
	mapping["STRAIN"] = "Indicates the amount of deformation per unit length of an object when a load is applied";
	mapping["SYSTEM"] = "A condition representing something that is not the operator, program, or hardware. This is often used for operating system issues.";
	mapping["TEMPERATURE"] = "Indicates the temperature of a component.";
	mapping["TILT"] = "The measure of angular displacement";
	mapping["TORQUE"] = "The measured of the turning force exerted on an object or by an object";
	mapping["VOLT_AMPERAGE"] = "The measure of the apparent power in an electrical circuit (commonly referred to as VA)";
	mapping["VOLT_AMPERAGE_REACTIVE"] = "The measure of reactive power in an AC electrical power circuit (commonly referred to as var).";
	mapping["VELOCITY"] = "Indicated the velocity of a component.";
	mapping["VISCOSITY"] = "The measure of a fluid’s resistance to flow";
	mapping["VOLTAGE"] = "The measurement of electrical potential between two points";
	mapping["WATTAGE"] = "The measurement of power consumed or dissipated by an electrical circuit or device ";

	mapping["ACCELERATION"] ="Rate of change of velocity"; 
	mapping["ACCUMULATED_TIME"] ="The measurement of accumulated time associated with a component"; 
	mapping["ANGULAR_ACCELERATION"] ="Rate of change of angular velocity."; 
	mapping["ANGULAR_VELOCITY"] ="Rate of change of angular position."; 
	mapping["AMPERAGE"] ="The measurement of AC Current or a DC current. Subtypes: ALTERNATING The measurement of alternating current.   If not specified further in Statistic, defaults to RMS Current   units in AMPERE.  DIRECT The measurement of DC current units in AMPERE."; 
	mapping["ANGLE"] ="The angular position of a component relative to the parent. ACTUAL The angular position as read from the physical component in units DEGREE.  COMMANDED - The angular position computed by the controller in units DEGREE."; 
	mapping["AXIS_FEEDRATE"] ="The feedrate of a linear axis.  Subtypes: ACTUAL - The actual federate of a linear axis in units MILLIMETER/SECOND. OMMANDED - The feedrate as specified in the program in units MILLIMETER/SECOND. OVERRIDE - The operator’s overridden value. Percent of commanded in units PERCENT."; 
	mapping["CLOCK_TIME"] ="The reading of a timing device at a specific point in time.   Clock time SHALL be reported in W3C ISO 8601 format."; 
	mapping["CONCENTRATION"] ="Percentage of one component within a mixture of components"; 
	mapping["CONDUCTIVITY"] ="The ability of a material to conduct electricity"; 
	mapping["DISPLACEMENT"] ="The displacement as the change in position of an object"; 
	mapping["ELECTRICAL_ENERGY"] ="The measurement of electrical energy consumption by a component"; 
	mapping["FILL_LEVEL"] ="The measurement of the amount of a substance remaining compared to the planned maximum amount of that substance                                                                                  "; 
	mapping["FLOW"] ="The rate of flow of a fluid "; 
	mapping["FREQUENCY"] ="The measurement of the number of occurrences of a repeating event per unit time"; 
	mapping["GLOBAL_POSITION"] ="Deprecated in Rel. 1.1"; 
	mapping["LEVEL"] =" Deprecated in Rel. 1.2  See Fill_Level"; 
	mapping["LINEAR_FORCE"] ="The measure of the push or pull introduced by an actuator or exerted on an object"; 
	mapping["LOAD"] ="The measurement of the percentage of the standard rating of a device"; 
	mapping["MASS"] ="The measurement of the mass of an object(s) or an amount of material"; 
	mapping["PATH_FEEDRATE"] ="The feedrate of the tool path. Subtypes: ACTUAL - The three-dimensional feedrate derived from all components in units MILLIMETER/SECOND. COMMANDED - The feedrate as specified in the program in units MILLIMETER/SECOND.  OVERRIDE - The operator’s overridden value. Percent of commanded in unitsPERCENT."; 
	mapping["PATH_POSITION"] ="The current program control point or program coordinate in WORK coordinates. The coordinate system will revert to MACHINE coordinates if WORK coordinates are not available.   ACTUAL The position of the component as read from the device in units   MILLIMETER_3D.  COMMANDEDThe position computed by the controller in units   MILLIMETER_3D.  TARGET The target position for the movement in units   MILLIMETER_3D.  PROBE The position provided by a probe in units   MILLIMETER_3D."; 
	mapping["PH"] ="The measure of the acidity or alkalinity."; 
	mapping["POSITION"] ="The position of the component. Defaults to MACHINE coordinates. Subtypes: ACTUAL-The position of the component as read from the device in units  MILLIMETER. COMMANDED- The position as given by the Controller in units MILLIMETER.  TARGET- The target position for the movement in units - MILLIMETER."; 
	mapping["POWER_FACTOR"] ="The measurement of the ratio of real power flowing to a load to the apparent power in that AC circuit."; 
	mapping["PRESSURE"] ="The force per unit area exerted by a gas or liquid"; 
	mapping["RESISTANCE"] ="The measurement of the degree to which an object opposes an electric current through it"; 
	mapping["ROTARY_VELOCITY"] ="The rotational speed of a rotary axis.  ACTUAL The rotational speed the rotary axis is spinning at. ROTARY_MODE SHALL be SPINDLE in units REVOLUTION/MINUTE  COMMANDED The rotational speed as specified in the program in units REVOLUTION/MINUTE.  OVERRIDE The operator’s overridden value. Percent of commanded in units PERCENT."; 
	mapping["SOUND_LEVEL"] ="Measurement of a sound level or sound pressure level relative to atmospheric pressure. Subtypes: NO_SCALE - No weighting factor on the frequency scale in DECIBEL.  A_SCALE A Scale weighting factor.   This is the default weighting factor if no factor is specified in DECIBEL. B_SCALE- B Scale weighting factor in DECIBEL.  C_SCALE C Scale weighting factor in DECIBEL.  D_SCALE D Scale weighting factor in  DECIBEL."; 
	mapping["SPINDLE_SPEED"] ="DEPRECATED in REL 1.2.     Replaced by ROTARY_VELOCITY"; 
	mapping["STRAIN"] ="Strain is the amount of deformation per unit length of an object when a load is applied.                                                       "; 
	mapping["TEMPERATURE"] ="The measurement of temperature"; 
	mapping["TILT"] ="A measurement of angular displacement "; 
	mapping["TORQUE"] ="The turning force exerted on an object or by an object"; 
	mapping["VOLT_AMPERE"] ="The measure of the apparent power in an electrical circuit, equal to the product of root-mean-square (RMS) voltage and RMS current’ (commonly referred to as VA)"; 
	mapping["VOLT_AMPERE_REACTIVE"] ="The measurement of reactive power in an AC electrical circuit (commonly referred to as var)"; 
	mapping["VELOCITY"] ="The rate of change of position."; 
	mapping["VISCOSITY"] ="A measurement of a fluid’s resistance to flow"; 

	mapping["ACTUAL"] ="The value of the component as read from the device."; 
	mapping["COMMANDED"] ="The value computed by the controller."; 
	mapping["TARGET"] ="The target value for the movement."; 
	mapping["PROBE"] ="The value provided by a probe"; 

	mapping["OVERRIDE"] ="The operator’s overridden value. Percent of commanded.";
	mapping["ALTERNATING"] ="The measurement of alternating current.   If not specified further in Statistic, defaults to RMS Current";  
	mapping["DIRECT"] ="The measurement of DC current";
	mapping["NO_SCALE"] ="No weighting factor on the frequency scale";
	mapping["A_SCALE"] ="A Scale weighting factor.   This is the default weighting factor if no factor is specified";
	mapping["B_SCALE"] ="B Scale weighting factor";
	mapping["C_SCALE"] ="C Scale weighting factor";
	mapping["D_SCALE"] ="D Scale weighting factor";
	mapping["ALTERNATING"] ="The measurement of alternating voltage.   If not specified further in Statistic, defaults to RMS voltage "; 
	mapping["DIRECT"] ="The measurement of DC voltage";
	mapping["CENTIPOISE"] ="A measure of Viscosity";
	mapping["DEGREE/MINUTE"]="Rotational velocity in degrees per minute";
	mapping["FAHRENHEIT"] ="Temperature in Fahrenheit";
	mapping["FOOT"] ="Feet";
	mapping["FOOT/MINUTE"] ="Feet per minute";
	mapping["FOOT/SECOND"] ="Feet per second";
	mapping["FOOT/SECOND^2"] ="Acceleration in feet per second squared";
	mapping["FOOT_3D"] ="A point in space identified by X, Y, and Z positions and represented by a space delimited set of numbers each expressed in feet.";
	mapping["GALLON/MINUTE"] ="Gallons per minute.";
	mapping["INCH"] ="Inches";
	mapping["INCH/MINUTE"] ="Inches per minute";
	mapping["INCH/SECOND"] ="Inches per second";
	mapping["INCH/SECOND^2"] ="Acceleration in inches per second squared";
	mapping["INCH_3D"] ="A point in space identified by X, Y, and Z positions and represented by a space delimited set of numbers each expressed in inches.";
	mapping["INCH_POUND"] ="A measure of torque in inch pounds.";
	mapping["KILOWATT"] ="A measurement in  kilowatt.";
	mapping["KILOWATT_HOUR"] ="Kilowatt hours which is 3.6 mega joules.";
	mapping["LITER"] ="Measurement of volume of a fluid";
	mapping["LITER/MINUTE"] ="Measurement of rate of flow of a fluid";
	mapping["MILLIMETER/MINUTE"] ="Velocity in millimeters per minute";
	mapping["POUND"] ="US pounds";
	mapping["POUND/INCH^2"] ="Pressure in pounds per square inch (PSI).";
	mapping["RADIAN	Angle"] =" in radians";
	mapping["RADIAN/SECOND"] ="Velocity in radians per second";
	mapping["RADIAN/SECOND^2"] ="Rotational acceleration in radian per second squared";
	mapping["RADIAN/MINUTE"] ="Velocity in radians per second.";
	mapping["REVOLUTION/SECOND"] ="Rotational velocity in revolution per second";
	mapping["OTHER"] ="Unsupported units";

	mapping["AVERAGE"] ="Mathematical Average value calculated for the DataItem during the calculation period";
	mapping["KURTOSIS"] ="A measure of the “peakedness” of a probability distribution; i.e., the shape of the distribution curve";
	mapping["MAXIMUM"] ="Maximum or peak value recorded for the DataItem during the calculation period";
	mapping["MEDIAN"] ="The middle number of a series of numbers";
	mapping["MINIMUM"] ="Minimum value recorded for the DataItem during the calculation period";
	mapping["MODE"] ="The number in a series of numbers that occurs most often";
	mapping["RANGE"] ="Difference between the Maximum value and Minimum value of a DataItem during the calculation period.  Also represents Peak-to-Peak measurement in an waveform.";
	mapping["ROOT_MEAN_SQUARE"] ="Mathematical Root Mean Value (RMS) value calculated for the DataItem during the calculation period";
	mapping["STANDARD_DEVIATION"] ="Statistical Standard Deviation value calculated for the DataItem during the calculation period";


	mapping["PASCAL"] ="Pressure in Newtons per square meter ";
	mapping["PASCAL_SECOND"] ="Measurement of Viscosity";
	mapping["PERCENT"] ="Percentage";
	mapping["PH"] ="A measure of the acidity or alkalinity of a solution";
	mapping["REVOLUTION/MINUTE"] ="Revolutions per minute";
	mapping["SECOND"] ="A measurement of time.";
	mapping["SIEMENS/METER"] ="A measurement of Electrical Conductivity";
	mapping["VOLT"] ="Volts";
	mapping["VOLT_AMPERE"] ="Volt-Ampere  (VA)";
	mapping["VOLT_AMPERE_REACTIVE"] ="Volt-Ampere Reactive  (var)";
	mapping["WATT"] ="Watts";
	mapping["WATT_SECOND"] ="Measurement of electrical energy, equal to one Joule";
	mapping["AMPERE"] ="Amps";
	mapping["CELSIUS"] ="Degrees Celsius";
	mapping["COUNT"] ="A counted event";
	mapping["DECIBEL"] ="Sound Level";
	mapping["DEGREE"] ="Angle in degrees";
	mapping["DEGREE/SECOND"] ="Angular degrees per second";
	mapping["DEGREE/SECOND^2"] ="Angular acceleration in degrees per second squared";
	mapping["HERTZ"] ="Frequency measured in cycles per second";
	mapping["JOULE"] ="A measurement of energy.";
	mapping["KILOGRAM"] ="Kilograms";
	mapping["LITER"] ="Liters";
	mapping["LITER/SECOND"] ="Liters per second";
	mapping["MICRO_RADIAN"] ="Measurement of Tilt";
	mapping["MILLIMETER"] ="Millimeters";
	mapping["MILLIMETER/SECOND"] ="Millimeters per second";
	mapping["MILLIMETER/SECOND^2"] ="Acceleration in millimeters per second squared";
	mapping["MILLIMETER_3D"] ="A point in space identified by X, Y, and Z positions and represented by a space delimited set of numbers each expressed in millimeters.";
	mapping["NEWTON"] ="Force in Newtons";
	mapping["NEWTON_METER"] ="Torque, a unit for force times distance."; 
	mapping["OHM"] ="Measure of Electrical Resistance";
	mapping["ACTUATOR_STATE"] ="The state of the actuator. ACTIVE or INACTIVE.";
	mapping["ALARM"] ="DEPRECATED: Replaced with CONDITION category.  Rel. 1.1.";
	mapping["ACTIVE_AXES"] ="The set of axes associated with a path that the controller is controlling. If this data item is not provided, it will be assumed the controller is controlling all axes.";
	mapping["AVAILABILITY"] ="Represents the components ability to communicate its availability. This SHALL be"
		"provided for the device and MAY be provided for all other components";
	mapping["AXIS_COUPLING"] ="Describes the way the axes will be associated to each other. This is used in conjunction with COUPLED_AXES to indicate the way they are interacting. The possible values are: TANDEM, SYNCHRONOUS, MASTER, and SLAVE. The coupling SHALL be viewed from the perspective of the axis, therefore a MASTER coupling indicates that this axis is the "
		"master of the COUPLED_AXES.";
	mapping["BLOCK"] ="The block of code being executed. The block contains the entire expression of the step in the program.";
	mapping["CODE"] ="DEPRECATED. Rel 1.1.0";
	mapping["CONTROLLER_MODE"] ="The current controller’s mode.  AUTOMATIC, MANUAL, MANUAL_DATA_INPUT, FEED_HOLD, or SEMI_AUTOMATIC.";
	mapping["COUPLED_AXES"] ="Refers to the set of associated axes. The value will be a space delimited set of axes names.";
	mapping["DIRECTION"] ="The direction of motion.  CLOCKWISE or COUNTER_CLOCKWISE";
	mapping["ROTARY"] ="The rotational direction of a rotary device.   CLOCKWISE or COUNTER_CLOCKWISE";
	mapping["LINEA"] ="R	The direction of motion of a linear device.   POSTIVE or NEGATIVE";
	mapping["DOOR_STATE"] ="The opened or closed state of the door. OPEN, UNLATCHED, or CLOSED.";
	mapping["EMERGENCY_STOP"]= "The current state of the emergency stop actuator. ARMED (the circuit is complete and the device is operating) or TRIGGERED (the circuit is open and the device SHALL cease operation).";
	mapping["EXECUTION"] ="The execution status of the Controller. READY, ACTIVE, INTERRUPTED, or STOPPED";
	mapping["LINE"] ="The current line of code being executed";
	mapping["MESSAGE"] ="An uninterpreted textual notification.";
	mapping["PART_COUNT"] ="The current count of parts produced as represented by the controller. SHALL be an integer value."
		"ALL	The count of all the parts produced. If the subtype is not given, this is the default. "
		"GOOD	Indicates the count of correct parts made. "
		"BAD	Indicates the count of incorrect parts produced.";
	mapping["PART_ID"] ="An identifier of the current part in the device";
	mapping["PATH_MODE"] ="The operational mode for this Path. SYNCHRONOUS, MIRROR, or INDEPENDENT. Default value is INDEPENDENT if not specified.";
	mapping["POWER_STATE"] ="The ON or OFF status of the component. DEPRECATION WARNING: MAY be"
		"deprecated in the future.";
	mapping["LINE"] ="The state of the high voltage line.";
	mapping["CONTROL"] ="The state of the low power line.";
	mapping["POWER_STATUS"] ="DEPRECATED.  Rel. 1.1.";
	mapping["PROGRAM"] ="The name of the program being executed";
	mapping["ROTARY_MODE"] ="The mode for the Rotary axis. SPINDLE, INDEX, or CONTOUR.";
	mapping["TOOL_ID"] ="DEPRECATED in Rel. 1.2.   See Tool_ASSET_ID.  The identifier of the tool currently in use for a given Path";
	mapping["TOOL_ASSET_ID"] ="The identifier of the tool currently in use for a given Path";
	mapping["WORKHOLDING_ID"] ="The identifier for the workholding currently in use for a given Path";

	mapping["UNAVAILABLE"]="No data item reading for this device is avaiable.";
	mapping["CLOSED"]="The door is closed to the point of a positive confirmation";
	mapping["INDETERMINATE"]="The door is not closed to the point of a positive confirmation and not open to the point of a positive confirmation.";
	mapping["OPEN"]="The door is open to the point of a positive confirmation.";
	mapping["MASTER"]="The axis is the master of the CoupledAxes";	
	mapping["SLAVE"]="The axis is a slave of the CoupledAxes";
	mapping["SYNCHRONOUS"]= "The axes are coupled and are operating together in lockstep.";	
	mapping["TANDEM"]= "The axes are physically connected to each other and SHALL operate as a single unit.";
	mapping["MACHINE"]= "Unchangeable coordinate system that has machine zero as its origin.";
	mapping["WORK"]= "The coordinate system that represents the working area for a particular workpiece whose origin is shifted within the MACHINE coordinate system. If the WORK coordinates are not currently defined in the device, the MACHINE coordinates will be used.";
	mapping["VALUE"]= "The measured value of a Sample.   If no representation is specified for a data item, the representation SHALL be determined to be VALUE.";
	mapping["TIME_SERIES"]= "A series of sampled data.  The data is collected for a specified number of samples and each sample is collected with a fixed period";
	mapping["ARMED"]= "The circuit is complete and the device is operating)";
	mapping["TRIGGERED"]= "The circuit is open and the device SHALL cease operation).";

	mapping["CLOCKWISE"]= "The rotary component is rotating in a clockwise fashion using the right hand rule.";
	mapping["COUNTER_CLOCKWISE"]= "The rotary component is rotating in a counter clockwise fashion using the right hand rule.";
	mapping["POSITIVE"]= "A linear component moving in the direction of increasing position value ";
	mapping["NEGATIVE"]= "A linear component moving in the direction of decreasing position value";


	mapping["AUTOMATIC"]= "Machine mode that allows an operator to execute a part program on the  CNC machine.";
	mapping["MANUAL"]= "Machine mode where CNC machine behaves like a standard or conventional machine.";	
	mapping["MANUAL_DATA_INPUT"]= "Machine mode whereby the operator can enter data through the keyboard on the control panel and display screen. In MDI mode, CNC commands are entered through the keyboard and display screen manually and can be executed once.";
	mapping["SEMI_AUTOMATIC"]= "";
	mapping["READY"]= "The controller is ready to execute. It is currently idle.";
	mapping["ACTIVE"]= "The controller is actively executing an instruction.";
	mapping["INTERRUPTED"]= "The operator or the program has paused execution and is waiting to be continued.";
	mapping["STOPPED"]= "The controller has been stopped.";
	mapping["ARMED"]= "The circuit is complete and the device is operating.";
	mapping["TRIGGERED"]= "The circuit is open and the device SHALL cease operation.";
	mapping["INDEPENDENT"]= "A set of axes are operating independently and without the influence of another set of axes.";
	mapping["SYNCHRONOUS"]= "The sets of axes are operating synchronously.";
	mapping["MIRROR"]= "The sets of axes are mirroring each other.";
	mapping["SPINDLE"]= "The axis is operating like a spindle and spinning.";
	mapping["INDEX"]= "The axis is indexing to a position.";
	mapping["CONTOUR"]= "The axis is interpolating its position as part of the path position defined by the controller.";

}

std::map<std::string, std::string> COpcUaGenerator::unitmapping;
void COpcUaGenerator::InitUnitMapping()
{
	unitmapping["AccelerationType"]= "MILLIMETER/SECOND^2";
	unitmapping["AccumulatedTimeType"]= "SECOND";	
	unitmapping["AmperageType"]= "AMPERE";
	unitmapping["AngleType"]= "DEGREE";	
	unitmapping["AngularAccelerationType"]= "DEGREE/SECOND^2";	
	unitmapping["AngularVelocityType"]= "DEGREE/SECOND";	
	unitmapping["AxisFeedrateType"]= "MILLIMETER/SECOND or PERCENT for override ";	
	unitmapping["ClockTimeType"]= "W3C ISO 8601 format of  YYYY-MM-DDThh:mm:ss.ffff";	


	unitmapping["ConcentrationType"]= "PERCENT";	
	unitmapping["ConductivityType"]= "SIEMENS/METER";	
	unitmapping["DisplacementType"]= "MILLIMETER";	
	unitmapping["ElectricalEnergyType"]= "WATT_SECOND";	
	unitmapping["FlowType"]= "LITER/SECOND";	
	unitmapping["FrequencyType"]= "HERTZ";	
	unitmapping["GlobalPositionType"]= "";	
	unitmapping["FillLevelType"]= "PERCENT";	
	unitmapping["LinearForceType"]= "NEWTON";	
	unitmapping["LoadType"]= "PERCENT";	
	unitmapping["MassType"]= "KILOGRAM";	


	unitmapping["PathFeedrateType"]= "MILLIMETER/SECOND or PERCENT for Override";	
	unitmapping["PathPositionType"]= "default to WORK coordinates in MILLIMETER_3D ";	
	unitmapping["PositionType"]= "MILLIMETER";	
	unitmapping["PowerFactorType"]= "PERCENT";	
	unitmapping["PressureType"]= "PASCAL";	
	unitmapping["ResistanceType"]= "OHM";	
	unitmapping["RotationalVelocityType"]= "REVOLUTION/MINUTE or PERCENT for Override";	
	unitmapping["SoundPressureType"]= "DECIBEL";	
	unitmapping["SpindleSpeedType"]= "";	
	unitmapping["StrainType"]= "PERCENT";	
	unitmapping["TemperatureType"]= "degrees CELSIUS ";	
	unitmapping["TiltType"]= "MICRO_RADIAN";	
	unitmapping["TorqueType"]= "NEWTON_METER";	
	unitmapping["VelocityType"]= "MILLIMETER/SECOND";	
	unitmapping["ViscosityType"]= "PASCAL_SECOND";	
	unitmapping["VoltageType"]= "VOLT";	
	unitmapping["VoltsType"]= "VOLT";	
	unitmapping["WattType"]= "WATT";	
	unitmapping["WattageType"]= "WATT";

}