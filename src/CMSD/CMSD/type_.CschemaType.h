#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CschemaType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CschemaType

#include "type_xs.CopenAttrs.h"


namespace CMSD
{

class CschemaType : public ::CMSD::xs::CopenAttrs
{
public:
	CMSD_EXPORT CschemaType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CschemaType(CschemaType const& init);
	void operator=(CschemaType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CschemaType); }

	MemberAttribute<string_type,_altova_mi_altova_CschemaType_altova_targetNamespace, 0, 0> targetNamespace;	// targetNamespace CanyURI

	MemberAttribute<string_type,_altova_mi_altova_CschemaType_altova_version, 0, 0> version;	// version Ctoken
	MemberAttribute<string_type,_altova_mi_altova_CschemaType_altova_finalDefault, 1, 5> finalDefault;	// finalDefault CfullDerivationSet
	MemberAttribute<string_type,_altova_mi_altova_CschemaType_altova_blockDefault, 1, 4> blockDefault;	// blockDefault CblockSet
	MemberAttribute<string_type,_altova_mi_altova_CschemaType_altova_attributeFormDefault, 0, 2> attributeFormDefault;	// attributeFormDefault CformChoice
	MemberAttribute<string_type,_altova_mi_altova_CschemaType_altova_elementFormDefault, 0, 2> elementFormDefault;	// elementFormDefault CformChoice

	MemberAttribute<string_type,_altova_mi_altova_CschemaType_altova_id, 0, 0> id;	// id CID
	MemberAttribute<string_type,_altova_mi_altova_CschemaType_altova_lang, 0, 1> lang;	// lang ClangType
	MemberElement<CincludeType, _altova_mi_altova_CschemaType_altova_include> include;
	struct include { typedef Iterator<CincludeType> iterator; };
	MemberElement<CimportType, _altova_mi_altova_CschemaType_altova_import> import;
	struct import { typedef Iterator<CimportType> iterator; };
	MemberElement<CredefineType, _altova_mi_altova_CschemaType_altova_redefine> redefine;
	struct redefine { typedef Iterator<CredefineType> iterator; };
	MemberElement<CannotationType, _altova_mi_altova_CschemaType_altova_annotation> annotation;
	struct annotation { typedef Iterator<CannotationType> iterator; };
	MemberElement<xs::CtopLevelSimpleType, _altova_mi_altova_CschemaType_altova_simpleType> simpleType;
	struct simpleType { typedef Iterator<xs::CtopLevelSimpleType> iterator; };
	MemberElement<xs::CtopLevelComplexType, _altova_mi_altova_CschemaType_altova_complexType> complexType;
	struct complexType { typedef Iterator<xs::CtopLevelComplexType> iterator; };
	MemberElement<xs::CnamedGroup, _altova_mi_altova_CschemaType_altova_group> group;
	struct group { typedef Iterator<xs::CnamedGroup> iterator; };
	MemberElement<xs::CnamedAttributeGroup, _altova_mi_altova_CschemaType_altova_attributeGroup> attributeGroup;
	struct attributeGroup { typedef Iterator<xs::CnamedAttributeGroup> iterator; };
	MemberElement<xs::CtopLevelElement, _altova_mi_altova_CschemaType_altova_element> element;
	struct element { typedef Iterator<xs::CtopLevelElement> iterator; };
	MemberElement<xs::CtopLevelAttribute, _altova_mi_altova_CschemaType_altova_attribute> attribute;
	struct attribute { typedef Iterator<xs::CtopLevelAttribute> iterator; };
	MemberElement<CnotationType, _altova_mi_altova_CschemaType_altova_notation> notation;
	struct notation { typedef Iterator<CnotationType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CschemaType
