#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CimportType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CimportType

#include "type_xs.Cannotated.h"


namespace CMSD
{

class CimportType : public ::CMSD::xs::Cannotated
{
public:
	CMSD_EXPORT CimportType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CimportType(CimportType const& init);
	void operator=(CimportType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CimportType); }

	MemberAttribute<string_type,_altova_mi_altova_CimportType_altova_namespace2, 0, 0> namespace2;	// namespace CanyURI

	MemberAttribute<string_type,_altova_mi_altova_CimportType_altova_schemaLocation, 0, 0> schemaLocation;	// schemaLocation CanyURI
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CimportType
