#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CnotationType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CnotationType

#include "type_xs.Cannotated.h"


namespace CMSD
{

class CnotationType : public ::CMSD::xs::Cannotated
{
public:
	CMSD_EXPORT CnotationType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CnotationType(CnotationType const& init);
	void operator=(CnotationType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CnotationType); }

	MemberAttribute<string_type,_altova_mi_altova_CnotationType_altova_name, 0, 0> name;	// name CNCName

	MemberAttribute<string_type,_altova_mi_altova_CnotationType_altova_public2, 0, 0> public2;	// public Cpublic

	MemberAttribute<string_type,_altova_mi_altova_CnotationType_altova_system2, 0, 0> system2;	// system CanyURI
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CnotationType
