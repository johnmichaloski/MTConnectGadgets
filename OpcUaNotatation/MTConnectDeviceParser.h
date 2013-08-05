//
// MTConnectDeviceParser.h
//

#pragma once

//#pragma comment( lib, "msxml2.lib" )
#import <msxml6.dll>
#include <string>
#include <boost/tuple/tuple.hpp>
#include <vector>
#include <map>


// name, type, id
//typedef boost::tuple<std::string, STORETYPE, std::string > DataModel;
//typedef std::vector<DataModel> DeviceModel;
//typedef std::map<std::string, STORETYPE> DataDictionary;
//typedef std::map<std::string, std::string> DataDictionary;

struct CDataItem
{
	std::string id;
	std::string name;
	std::string type;
	std::string subType;
	std::string category;
	std::string units;
	std::string nativeUnits;
	std::string value;
};

typedef std::map<std::string, CDataItem> MTConnectDataModel;

class MTConnectDeviceParser
{
	MSXML2::IXMLDOMSchemaCollectionPtr m_pSchemaCache;
	MSXML2::IXMLDOMDocumentPtr         m_pXSDDoc;
	MSXML2::IXMLDOMDocument2Ptr        m_pXMLDoc;
	// Handling the device specification or probe?
	std::string _devicesfilename;

public:

	MTConnectDeviceParser(void);
	~MTConnectDeviceParser(void);
	_bstr_t ParseXMLDocument(_bstr_t xmlfile, _bstr_t xsdfile="", _bstr_t xsdname="");
	_bstr_t GetAttribute(MSXML2::IXMLDOMNodePtr node, _bstr_t attribute);
	MTConnectDataModel ReadDeviceDescription(std::string filename);

	//MTConnectDataModel dataItems;
};
