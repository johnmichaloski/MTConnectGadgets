#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CselectorType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CselectorType

#include "type_xs.Cannotated.h"


namespace CMSD
{

namespace xs
{	

class CselectorType : public ::CMSD::xs::Cannotated
{
public:
	CMSD_EXPORT CselectorType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CselectorType(CselectorType const& init);
	void operator=(CselectorType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_xs_altova_CselectorType); }

	MemberAttribute<string_type,_altova_mi_xs_altova_CselectorType_altova_xpath, 0, 0> xpath;	// xpath CxpathType
};



} // namespace xs

}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CselectorType
