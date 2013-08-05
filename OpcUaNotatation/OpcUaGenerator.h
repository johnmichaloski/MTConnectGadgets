//
// OpcUaGenerator.h
//

#pragma once
#import <msxml6.dll>
#include <string>
#include <vector>
#include <map>
#include <comdef.h>
struct AttrType
{
	std::string _name;
	std::string _type;
	std::string _use;

};
struct ElemType
{
	std::string _name;
	std::string _type;
	std::string _minOccurs;
	std::string _maxOccurs;
	std::string _doc;
	std::string _substitutionGroup;

};
struct SimpleType
{
	std::string _name;
	std::string _type;
	std::map<std::string, std::string> _enum;
	std::string _doc;
	std::vector<std::string> _union;

};

struct ComplexType
{
	std::string _doc;
	std::string _baseClass;
	std::string _abstract;
	std::string _type;
	std::string _minOccurs;
	std::string _maxOccurs;
	std::vector<AttrType> _attr;
	std::vector<ElemType> _seq;
	std::map<std::string, std::string> _enum;

};
class COpcUaGenerator
{
	MSXML2::IXMLDOMSchemaCollectionPtr m_pSchemaCache;
	MSXML2::IXMLDOMDocumentPtr         m_pXSDDoc;
	MSXML2::IXMLDOMDocument2Ptr        m_pXMLDoc;
	std::string HtmlStyle();
	std::map<std::string, SimpleType> _SimpleTypes;
	std::map<std::string, ComplexType> _ComplexTypes;
	std::map<std::string, ElemType> _Elements;
	std::vector<std::string> _StringSimpleTypes;
	static std::map<std::string, std::string> mapping;
	static std::map<std::string, std::string> unitmapping;
	
	void InitMapping();
	void InitUnitMapping();
	std::string GenerateElement(ElemType &elemtype);
	std::string GenerateEnumeration(std::string name, std::map<std::string, std::string> & enums);
	std::vector<AttrType> GetAttributes(MSXML2::IXMLDOMNodePtr pNode);
	bool IsUnusedType(std::string name);
	void UsedType(std::string name);
public:
	COpcUaGenerator(void);
	~COpcUaGenerator(void);
	void ReadXmlSchema(std::string xmlfilename);
	void Close();
	std::string  GenerateStreamsDocument(std::string xmloutputfilename);
	std::string GenerateAssetsDocument();
	std::string GenerateSensorsDocument();
	std::map<std::string, int> _UsedTypes;

	void MarkElementTypes(std::string elementName);
	void MarkComplexTypes(std::string typeName);
	void MarkSimpleTypes(std::string typeName);
	void MarkType(std::string typeName);

	void AddConditions();
	bool _bSampleTypes;
	void Clear();
};
