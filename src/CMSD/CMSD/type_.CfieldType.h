#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CfieldType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CfieldType

#include "type_xs.Cannotated.h"


namespace CMSD
{

class CfieldType : public ::CMSD::xs::Cannotated
{
public:
	CMSD_EXPORT CfieldType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CfieldType(CfieldType const& init);
	void operator=(CfieldType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CfieldType); }

	MemberAttribute<string_type,_altova_mi_altova_CfieldType_altova_xpath, 0, 0> xpath;	// xpath CxpathType
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CfieldType
