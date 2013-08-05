//
// MTConnectStreamsParser.cpp
//

#include "StdAfx.h"
#include "MTConnectStreamsParser.h"
#include "dcomutils.h"

#pragma comment(lib, "comsuppw.lib")
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Iphlpapi.lib")


ptime GetDateTime(std::string s)
{
	// parse 2012-02-03T17:31:51.0968Z 
	int Year, Month, Day, Hour, Minute, Second, Millisecond;
	if(sscanf(s.c_str(), "%d-%d-%dT%d:%d:%d.%d", &Year, &Month, &Day, &Hour, &Minute,&Second, &Millisecond)==7){}
		//12/2/2009 2:42:25 PM
	else if(sscanf(s.c_str(), "%d/%d/%4d%d:%d:%d", &Month, &Day, &Year,  &Hour, &Minute,&Second)==6){}
	else throw std::exception("Unrecognized date-time format\n");

	 return ptime( date(Year,Month,Day),
                  hours(Hour)  +
                  minutes(Minute) +
                  seconds(Second) +
                  boost::posix_time::millisec(int(Millisecond)) );

	//return COleDateTime( Year, Month, Day, Hour, Minute, Second ); 
}
static _bstr_t checkParseError(MSXML2::IXMLDOMParseErrorPtr pError)
{
	_bstr_t parseError =
		_bstr_t("<BR>") 
		+ _bstr_t(pError->line)
		+ _bstr_t("(") 
		+ _bstr_t(pError->linepos)
		+ _bstr_t("):") 
		+ pError->srcText
		+ _bstr_t("<BR> Error:") 
		+ pError->reason;
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
	

MTConnectStreamsParser::MTConnectStreamsParser(void)
{

}

MTConnectStreamsParser::~MTConnectStreamsParser(void)
{
}
void MTConnectStreamsParser::Release(void)
{
	m_pXSDDoc=NULL;
	m_pXMLDoc=NULL;
}

_bstr_t MTConnectStreamsParser::GetAttribute(MSXML2::IXMLDOMNodePtr node, _bstr_t attribute)
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

std::string MTConnectStreamsParser::ParseXMLDocument(_bstr_t xmlfile, _bstr_t xsdfile, _bstr_t xsdname)
{ 
	_bstr_t parseError(L"");
	try{
		MSXML2::IXMLDOMParseErrorPtr  pError;
		VARIANT_BOOL vbFlag;

		// load the XML file
		// ****** you need to use IXMLDOMDocument2 interface *********
		HRESULT hr = m_pXMLDoc.CreateInstance(__uuidof(MSXML2::DOMDocument60));
		m_pXMLDoc->async =  VARIANT_FALSE; 
		m_pXMLDoc->validateOnParse = VARIANT_FALSE; 
		//m_pXMLDoc->validateOnParse = VARIANT_TRUE; 

		hr = m_pXMLDoc->load(xmlfile);      

		//check on the parser error      
		if(hr!=VARIANT_TRUE)
		{
			return (LPCSTR) checkParseError(m_pXMLDoc->parseError);
		}

#if 1
		//load the XSD file
		if(xsdfile.length() == 0 )
			return (LPCSTR) parseError;

		hr = m_pXSDDoc.CreateInstance(__uuidof(MSXML2::DOMDocument60));
		m_pXSDDoc->async =  VARIANT_FALSE; 

		vbFlag = m_pXSDDoc->load(xsdfile );

		//check on the parser error      
		if(vbFlag!=VARIANT_TRUE)
		{         
			return (LPCSTR) checkParseError(m_pXSDDoc->parseError);
		}


		//create schemacache
		MSXML2::IXMLDOMSchemaCollectionPtr m_pSchemaCache;
		hr = m_pSchemaCache.CreateInstance(__uuidof(MSXML2::XMLSchemaCache60));
		m_pXMLDoc->schemas = m_pSchemaCache.GetInterfacePtr();

		//hook it up with XML Document
		hr = m_pSchemaCache->add("urn:mtconnect.org:MTConnectStreams:1.2",
			m_pXSDDoc.GetInterfacePtr());   



		//call validate 
		pError = m_pXMLDoc->validate();

		long lErrorCode; 
		hr = pError->get_errorCode(&lErrorCode);
		if(hr != S_FALSE)
		{
			return (LPCSTR) checkParseError(m_pXSDDoc->parseError);
			//parseError = _bstr_t("Error code: ") + _bstr_t(lErrorCode) 
			//	+ _bstr_t("\n") + _bstr_t("Reason: ")+ pError->Getreason();
			//MessageBox(NULL, (char*)parseError, "Parse Error",MB_OK);
		}
#endif
	}
	catch(_com_error &e)
	{
		dump_com_error(e);
		return  e.ErrorMessage();
	}

	return (LPCSTR) parseError;
}
