#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_Cannotated
#define _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_Cannotated

#include "type_xs.CopenAttrs.h"


namespace CMSD
{

namespace xs
{	

class Cannotated : public ::CMSD::xs::CopenAttrs
{
public:
	CMSD_EXPORT Cannotated(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT Cannotated(Cannotated const& init);
	void operator=(Cannotated const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_xs_altova_Cannotated); }

	MemberAttribute<string_type,_altova_mi_xs_altova_Cannotated_altova_id, 0, 0> id;	// id CID
	MemberElement<CannotationType, _altova_mi_xs_altova_Cannotated_altova_annotation> annotation;
	struct annotation { typedef Iterator<CannotationType> iterator; };
	CMSD_EXPORT void SetXsiType();
};



} // namespace xs

}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_Cannotated
