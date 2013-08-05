#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CunionType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CunionType

#include "type_xs.Cannotated.h"


namespace CMSD
{

class CunionType : public ::CMSD::xs::Cannotated
{
public:
	CMSD_EXPORT CunionType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CunionType(CunionType const& init);
	void operator=(CunionType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CunionType); }

	MemberAttribute<string_type,_altova_mi_altova_CunionType_altova_memberTypes, 0, 0> memberTypes;	// memberTypes CmemberTypesType
	MemberElement<xs::ClocalSimpleType, _altova_mi_altova_CunionType_altova_simpleType> simpleType;
	struct simpleType { typedef Iterator<xs::ClocalSimpleType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CunionType
