#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_Cwildcard
#define _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_Cwildcard

#include "type_xs.Cannotated.h"


namespace CMSD
{

namespace xs
{	

class Cwildcard : public ::CMSD::xs::Cannotated
{
public:
	CMSD_EXPORT Cwildcard(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT Cwildcard(Cwildcard const& init);
	void operator=(Cwildcard const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_xs_altova_Cwildcard); }
	MemberAttribute<string_type,_altova_mi_xs_altova_Cwildcard_altova_namespace2, 1, 4> namespace2;	// namespace CnamespaceList
	MemberAttribute<string_type,_altova_mi_xs_altova_Cwildcard_altova_processContents, 0, 3> processContents;	// processContents CprocessContentsType
	CMSD_EXPORT void SetXsiType();
};



} // namespace xs

}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_Cwildcard
