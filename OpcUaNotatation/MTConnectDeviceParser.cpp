//
// MTConnectDeviceParser.cpp
//

// This software was developed by U.S. Government employees as part of
// their official duties and is not subject to copyright. No warranty implied 
// or intended.

#include "StdAfx.h"
#include "MTConnectDeviceParser.h"
#include <iostream>
#include "StdStringFcn.h"

static _bstr_t checkParseError(MSXML2::IXMLDOMParseErrorPtr pError)
{
	_bstr_t parseError =_bstr_t("At line ")+ _bstr_t(pError->Getline()) + _bstr_t("\n")+ _bstr_t(pError->Getreason());
	MessageBox(NULL,parseError, "Parse Error",MB_OK);
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
	

MTConnectDeviceParser::MTConnectDeviceParser(void)
{
}

MTConnectDeviceParser::~MTConnectDeviceParser(void)
{
}

_bstr_t MTConnectDeviceParser::GetAttribute(MSXML2::IXMLDOMNodePtr node, _bstr_t attribute)
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

_bstr_t MTConnectDeviceParser::ParseXMLDocument(_bstr_t xmlfile, _bstr_t xsdfile, _bstr_t xsdname)
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
			return checkParseError(m_pXMLDoc->parseError);
		}
#if 0
		//load the XSD file
		if(xsdfile!=NULL)
		{
			hr = m_pXSDDoc.CreateInstance(__uuidof(MSXML2::DOMDocument));
			m_pXSDDoc->async =  VARIANT_FALSE; 

			hr = m_pXSDDoc->load(xsdfile /*"books.xsd"*/);

			//check on the parser error      
			if(hr!=VARIANT_TRUE)
			{         
				return checkParseError(m_pXSDDoc->parseError);
			}

			//create schemacache
			hr = m_pSchemaCache.CreateInstance(__uuidof(MSXML2::XMLSchemaCache));
			m_pXMLDoc->schemas = m_pSchemaCache.GetInterfacePtr();

			//hook it up with XML Document
			hr = m_pSchemaCache->add(xsdname /*"urn:books"*/, m_pXSDDoc.GetInterfacePtr());   

			//call validate 
			pError = m_pXMLDoc->validate();
		}
#endif
		//
		//if(pError->errorCode != S_OK)
		//{
		//	parseError = _bstr_t("Error code: ")+ _bstr_t(pError->errorCode) +_bstr_t("\n") + _bstr_t("Reason: ")+ pError->Getreason();
		//	MessageBox(NULL, (char*)parseError, "Parse Error",MB_OK);
		//}

	}
	catch(_com_error &e)
	{
		dump_com_error(e);
	}

	return parseError;
}

MTConnectDataModel MTConnectDeviceParser::ReadDeviceDescription(std::string filename)
{
	MTConnectDataModel dataItems;
	dataItems.clear();
	if(GetFileAttributesA(filename.c_str())== INVALID_FILE_ATTRIBUTES)
	{
		filename= ::ExeDirectory() + filename;
	}
	if(GetFileAttributesA(filename.c_str())== INVALID_FILE_ATTRIBUTES)
		throw std::exception("MTConnectDeviceParser::ReadDeviceDescription invalid devices file");

	_devicesfilename = filename;

	try{
		ParseXMLDocument(_devicesfilename.c_str());

		MSXML2::IXMLDOMNodePtr root = m_pXMLDoc->GetdocumentElement();
		MSXML2::IXMLDOMNodeListPtr nodes = root->selectNodes(_bstr_t("//DataItem"));
		for(int i=0; i< nodes->length; i++)
		{
			MSXML2::IXMLDOMNodePtr pNode = NULL;	
			CDataItem dataItem;
			nodes->get_item(i, &pNode);

			dataItem.name = (LPCSTR)  GetAttribute(pNode, "name");
			dataItem.category = (LPCSTR) GetAttribute(pNode, "category");
			dataItem.id = (LPCSTR) GetAttribute(pNode, "id");
			dataItem.type = (LPCSTR) GetAttribute(pNode, "type");
			dataItem.subType = (LPCSTR) GetAttribute(pNode, "subType");
			dataItem.units = (LPCSTR) GetAttribute(pNode, "units");
			dataItem.nativeUnits = (LPCSTR) GetAttribute(pNode, "nativeUnits");
			if(dataItem.type == "ASSET_CHANGED")
			{
				dataItem.category = "ASSET_CHANGED";
			}

			dataItem.category=MakeLower(dataItem.category);
			
			if(!dataItem.name.empty())
			{
				dataItems[dataItem.name]=dataItem;
			}
			// Could get name or id via SHDR
			else if(!dataItem.id.empty())
			{
				dataItems[dataItem.id]=dataItem;
			}
			else
			{
				continue;
			}
		}
	}
	catch(_com_error error)
	{
		std::cout << "MTConnectDeviceParser::ReadDeviceDescription" << error.ErrorMessage();
	}
	return dataItems;

}