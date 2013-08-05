#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CincludeType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CincludeType

#include "type_xs.Cannotated.h"


namespace CMSD
{

class CincludeType : public ::CMSD::xs::Cannotated
{
public:
	CMSD_EXPORT CincludeType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CincludeType(CincludeType const& init);
	void operator=(CincludeType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CincludeType); }

	MemberAttribute<string_type,_altova_mi_altova_CincludeType_altova_schemaLocation, 0, 0> schemaLocation;	// schemaLocation CanyURI
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CincludeType
