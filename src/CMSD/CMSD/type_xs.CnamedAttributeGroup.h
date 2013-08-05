#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CnamedAttributeGroup
#define _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CnamedAttributeGroup



namespace CMSD
{

namespace xs
{	

class CnamedAttributeGroup : public TypeBase
{
public:
	CMSD_EXPORT CnamedAttributeGroup(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CnamedAttributeGroup(CnamedAttributeGroup const& init);
	void operator=(CnamedAttributeGroup const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_xs_altova_CnamedAttributeGroup); }

	MemberAttribute<string_type,_altova_mi_xs_altova_CnamedAttributeGroup_altova_id, 0, 0> id;	// id CID

	MemberAttribute<string_type,_altova_mi_xs_altova_CnamedAttributeGroup_altova_name, 0, 0> name;	// name CNCName

	MemberAttribute<string_type,_altova_mi_xs_altova_CnamedAttributeGroup_altova_ref, 0, 0> ref;	// ref CQName
	MemberElement<CannotationType, _altova_mi_xs_altova_CnamedAttributeGroup_altova_annotation> annotation;
	struct annotation { typedef Iterator<CannotationType> iterator; };
	MemberElement<xs::Cattribute, _altova_mi_xs_altova_CnamedAttributeGroup_altova_attribute> attribute;
	struct attribute { typedef Iterator<xs::Cattribute> iterator; };
	MemberElement<xs::CattributeGroupRef, _altova_mi_xs_altova_CnamedAttributeGroup_altova_attributeGroup> attributeGroup;
	struct attributeGroup { typedef Iterator<xs::CattributeGroupRef> iterator; };
	MemberElement<xs::Cwildcard, _altova_mi_xs_altova_CnamedAttributeGroup_altova_anyAttribute> anyAttribute;
	struct anyAttribute { typedef Iterator<xs::Cwildcard> iterator; };
	CMSD_EXPORT void SetXsiType();
};



} // namespace xs

}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CnamedAttributeGroup
