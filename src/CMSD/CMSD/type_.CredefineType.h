#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CredefineType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CredefineType

#include "type_xs.CopenAttrs.h"


namespace CMSD
{

class CredefineType : public ::CMSD::xs::CopenAttrs
{
public:
	CMSD_EXPORT CredefineType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CredefineType(CredefineType const& init);
	void operator=(CredefineType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CredefineType); }

	MemberAttribute<string_type,_altova_mi_altova_CredefineType_altova_schemaLocation, 0, 0> schemaLocation;	// schemaLocation CanyURI

	MemberAttribute<string_type,_altova_mi_altova_CredefineType_altova_id, 0, 0> id;	// id CID
	MemberElement<CannotationType, _altova_mi_altova_CredefineType_altova_annotation> annotation;
	struct annotation { typedef Iterator<CannotationType> iterator; };
	MemberElement<xs::CtopLevelSimpleType, _altova_mi_altova_CredefineType_altova_simpleType> simpleType;
	struct simpleType { typedef Iterator<xs::CtopLevelSimpleType> iterator; };
	MemberElement<xs::CtopLevelComplexType, _altova_mi_altova_CredefineType_altova_complexType> complexType;
	struct complexType { typedef Iterator<xs::CtopLevelComplexType> iterator; };
	MemberElement<xs::CnamedGroup, _altova_mi_altova_CredefineType_altova_group> group;
	struct group { typedef Iterator<xs::CnamedGroup> iterator; };
	MemberElement<xs::CnamedAttributeGroup, _altova_mi_altova_CredefineType_altova_attributeGroup> attributeGroup;
	struct attributeGroup { typedef Iterator<xs::CnamedAttributeGroup> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CredefineType
