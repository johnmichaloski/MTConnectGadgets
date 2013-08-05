#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CsimpleType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CsimpleType

#include "type_xs.Cannotated.h"


namespace CMSD
{

namespace xs
{	

class CsimpleType : public ::CMSD::xs::Cannotated
{
public:
	CMSD_EXPORT CsimpleType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CsimpleType(CsimpleType const& init);
	void operator=(CsimpleType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_xs_altova_CsimpleType); }
	MemberAttribute<string_type,_altova_mi_xs_altova_CsimpleType_altova_final, 1, 4> final;	// final CsimpleDerivationSet

	MemberAttribute<string_type,_altova_mi_xs_altova_CsimpleType_altova_name, 0, 0> name;	// name CNCName
	MemberElement<CrestrictionType, _altova_mi_xs_altova_CsimpleType_altova_restriction> restriction;
	struct restriction { typedef Iterator<CrestrictionType> iterator; };
	MemberElement<ClistType, _altova_mi_xs_altova_CsimpleType_altova_list> list;
	struct list { typedef Iterator<ClistType> iterator; };
	MemberElement<CunionType, _altova_mi_xs_altova_CsimpleType_altova_union2> union2;
	struct union2 { typedef Iterator<CunionType> iterator; };
	CMSD_EXPORT void SetXsiType();
};



} // namespace xs

}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CsimpleType
