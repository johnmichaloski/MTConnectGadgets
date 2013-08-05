#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CextensionType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CextensionType

#include "type_xs.Cannotated.h"


namespace CMSD
{

namespace xs
{	

class CextensionType : public ::CMSD::xs::Cannotated
{
public:
	CMSD_EXPORT CextensionType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CextensionType(CextensionType const& init);
	void operator=(CextensionType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_xs_altova_CextensionType); }

	MemberAttribute<string_type,_altova_mi_xs_altova_CextensionType_altova_base, 0, 0> base;	// base CQName
	MemberElement<xs::CgroupRef, _altova_mi_xs_altova_CextensionType_altova_group> group;
	struct group { typedef Iterator<xs::CgroupRef> iterator; };
	MemberElement<xs::Call, _altova_mi_xs_altova_CextensionType_altova_all> all;
	struct all { typedef Iterator<xs::Call> iterator; };
	MemberElement<xs::CexplicitGroup, _altova_mi_xs_altova_CextensionType_altova_choice> choice;
	struct choice { typedef Iterator<xs::CexplicitGroup> iterator; };
	MemberElement<xs::CexplicitGroup, _altova_mi_xs_altova_CextensionType_altova_sequence> sequence;
	struct sequence { typedef Iterator<xs::CexplicitGroup> iterator; };
	MemberElement<xs::Cattribute, _altova_mi_xs_altova_CextensionType_altova_attribute> attribute;
	struct attribute { typedef Iterator<xs::Cattribute> iterator; };
	MemberElement<xs::CattributeGroupRef, _altova_mi_xs_altova_CextensionType_altova_attributeGroup> attributeGroup;
	struct attributeGroup { typedef Iterator<xs::CattributeGroupRef> iterator; };
	MemberElement<xs::Cwildcard, _altova_mi_xs_altova_CextensionType_altova_anyAttribute> anyAttribute;
	struct anyAttribute { typedef Iterator<xs::Cwildcard> iterator; };
	CMSD_EXPORT void SetXsiType();
};



} // namespace xs

}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CextensionType
