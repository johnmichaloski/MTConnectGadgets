#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CsimpleExtensionType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CsimpleExtensionType



namespace CMSD
{

namespace xs
{	

class CsimpleExtensionType : public TypeBase
{
public:
	CMSD_EXPORT CsimpleExtensionType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CsimpleExtensionType(CsimpleExtensionType const& init);
	void operator=(CsimpleExtensionType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_xs_altova_CsimpleExtensionType); }

	MemberAttribute<string_type,_altova_mi_xs_altova_CsimpleExtensionType_altova_id, 0, 0> id;	// id CID

	MemberAttribute<string_type,_altova_mi_xs_altova_CsimpleExtensionType_altova_base, 0, 0> base;	// base CQName
	MemberElement<CannotationType, _altova_mi_xs_altova_CsimpleExtensionType_altova_annotation> annotation;
	struct annotation { typedef Iterator<CannotationType> iterator; };
	MemberElement<xs::CgroupRef, _altova_mi_xs_altova_CsimpleExtensionType_altova_group> group;
	struct group { typedef Iterator<xs::CgroupRef> iterator; };
	MemberElement<xs::Call, _altova_mi_xs_altova_CsimpleExtensionType_altova_all> all;
	struct all { typedef Iterator<xs::Call> iterator; };
	MemberElement<xs::CexplicitGroup, _altova_mi_xs_altova_CsimpleExtensionType_altova_choice> choice;
	struct choice { typedef Iterator<xs::CexplicitGroup> iterator; };
	MemberElement<xs::CexplicitGroup, _altova_mi_xs_altova_CsimpleExtensionType_altova_sequence> sequence;
	struct sequence { typedef Iterator<xs::CexplicitGroup> iterator; };
	MemberElement<xs::Cattribute, _altova_mi_xs_altova_CsimpleExtensionType_altova_attribute> attribute;
	struct attribute { typedef Iterator<xs::Cattribute> iterator; };
	MemberElement<xs::CattributeGroupRef, _altova_mi_xs_altova_CsimpleExtensionType_altova_attributeGroup> attributeGroup;
	struct attributeGroup { typedef Iterator<xs::CattributeGroupRef> iterator; };
	MemberElement<xs::Cwildcard, _altova_mi_xs_altova_CsimpleExtensionType_altova_anyAttribute> anyAttribute;
	struct anyAttribute { typedef Iterator<xs::Cwildcard> iterator; };
	CMSD_EXPORT void SetXsiType();
};



} // namespace xs

}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CsimpleExtensionType
