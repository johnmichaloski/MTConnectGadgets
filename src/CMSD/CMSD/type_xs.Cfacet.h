#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_Cfacet
#define _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_Cfacet

#include "type_xs.Cannotated.h"


namespace CMSD
{

namespace xs
{	

class Cfacet : public ::CMSD::xs::Cannotated
{
public:
	CMSD_EXPORT Cfacet(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT Cfacet(Cfacet const& init);
	void operator=(Cfacet const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_xs_altova_Cfacet); }

	MemberAttribute<string_type,_altova_mi_xs_altova_Cfacet_altova_value2, 0, 0> value2;	// value CanySimpleType

	MemberAttribute<bool,_altova_mi_xs_altova_Cfacet_altova_fixed, 0, 0> fixed;	// fixed Cboolean
	CMSD_EXPORT void SetXsiType();
};



} // namespace xs

}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_Cfacet
