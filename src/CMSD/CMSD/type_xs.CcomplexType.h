#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CcomplexType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CcomplexType

#include "type_xs.Cannotated.h"


namespace CMSD
{

namespace xs
{	

class CcomplexType : public ::CMSD::xs::Cannotated
{
public:
	CMSD_EXPORT CcomplexType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CcomplexType(CcomplexType const& init);
	void operator=(CcomplexType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_xs_altova_CcomplexType); }

	MemberAttribute<string_type,_altova_mi_xs_altova_CcomplexType_altova_name, 0, 0> name;	// name CNCName

	MemberAttribute<bool,_altova_mi_xs_altova_CcomplexType_altova_mixed, 0, 0> mixed;	// mixed Cboolean

	MemberAttribute<bool,_altova_mi_xs_altova_CcomplexType_altova_abstract, 0, 0> abstract;	// abstract Cboolean
	MemberAttribute<string_type,_altova_mi_xs_altova_CcomplexType_altova_final, 1, 3> final;	// final CderivationSet
	MemberAttribute<string_type,_altova_mi_xs_altova_CcomplexType_altova_block, 1, 3> block;	// block CderivationSet
	MemberElement<CsimpleContentType, _altova_mi_xs_altova_CcomplexType_altova_simpleContent> simpleContent;
	struct simpleContent { typedef Iterator<CsimpleContentType> iterator; };
	MemberElement<CcomplexContentType, _altova_mi_xs_altova_CcomplexType_altova_complexContent> complexContent;
	struct complexContent { typedef Iterator<CcomplexContentType> iterator; };
	MemberElement<xs::CgroupRef, _altova_mi_xs_altova_CcomplexType_altova_group> group;
	struct group { typedef Iterator<xs::CgroupRef> iterator; };
	MemberElement<xs::Call, _altova_mi_xs_altova_CcomplexType_altova_all> all;
	struct all { typedef Iterator<xs::Call> iterator; };
	MemberElement<xs::CexplicitGroup, _altova_mi_xs_altova_CcomplexType_altova_choice> choice;
	struct choice { typedef Iterator<xs::CexplicitGroup> iterator; };
	MemberElement<xs::CexplicitGroup, _altova_mi_xs_altova_CcomplexType_altova_sequence> sequence;
	struct sequence { typedef Iterator<xs::CexplicitGroup> iterator; };
	MemberElement<xs::Cattribute, _altova_mi_xs_altova_CcomplexType_altova_attribute> attribute;
	struct attribute { typedef Iterator<xs::Cattribute> iterator; };
	MemberElement<xs::CattributeGroupRef, _altova_mi_xs_altova_CcomplexType_altova_attributeGroup> attributeGroup;
	struct attributeGroup { typedef Iterator<xs::CattributeGroupRef> iterator; };
	MemberElement<xs::Cwildcard, _altova_mi_xs_altova_CcomplexType_altova_anyAttribute> anyAttribute;
	struct anyAttribute { typedef Iterator<xs::Cwildcard> iterator; };
	CMSD_EXPORT void SetXsiType();
};



} // namespace xs

}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CcomplexType
