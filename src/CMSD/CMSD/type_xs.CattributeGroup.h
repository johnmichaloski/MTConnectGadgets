#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CattributeGroup
#define _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CattributeGroup

#include "type_xs.Cannotated.h"


namespace CMSD
{

namespace xs
{	

class CattributeGroup : public ::CMSD::xs::Cannotated
{
public:
	CMSD_EXPORT CattributeGroup(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CattributeGroup(CattributeGroup const& init);
	void operator=(CattributeGroup const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_xs_altova_CattributeGroup); }

	MemberAttribute<string_type,_altova_mi_xs_altova_CattributeGroup_altova_name, 0, 0> name;	// name CNCName

	MemberAttribute<string_type,_altova_mi_xs_altova_CattributeGroup_altova_ref, 0, 0> ref;	// ref CQName
	MemberElement<xs::Cattribute, _altova_mi_xs_altova_CattributeGroup_altova_attribute> attribute;
	struct attribute { typedef Iterator<xs::Cattribute> iterator; };
	MemberElement<xs::CattributeGroupRef, _altova_mi_xs_altova_CattributeGroup_altova_attributeGroup> attributeGroup;
	struct attributeGroup { typedef Iterator<xs::CattributeGroupRef> iterator; };
	MemberElement<xs::Cwildcard, _altova_mi_xs_altova_CattributeGroup_altova_anyAttribute> anyAttribute;
	struct anyAttribute { typedef Iterator<xs::Cwildcard> iterator; };
	CMSD_EXPORT void SetXsiType();
};



} // namespace xs

}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CattributeGroup
