#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CtopLevelAttribute
#define _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CtopLevelAttribute



namespace CMSD
{

namespace xs
{	

class CtopLevelAttribute : public TypeBase
{
public:
	CMSD_EXPORT CtopLevelAttribute(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CtopLevelAttribute(CtopLevelAttribute const& init);
	void operator=(CtopLevelAttribute const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_xs_altova_CtopLevelAttribute); }

	MemberAttribute<string_type,_altova_mi_xs_altova_CtopLevelAttribute_altova_id, 0, 0> id;	// id CID

	MemberAttribute<string_type,_altova_mi_xs_altova_CtopLevelAttribute_altova_name, 0, 0> name;	// name CNCName

	MemberAttribute<string_type,_altova_mi_xs_altova_CtopLevelAttribute_altova_ref, 0, 0> ref;	// ref CQName

	MemberAttribute<string_type,_altova_mi_xs_altova_CtopLevelAttribute_altova_type, 0, 0> type;	// type CQName
	MemberAttribute<string_type,_altova_mi_xs_altova_CtopLevelAttribute_altova_use, 0, 3> use;	// use CuseType

	MemberAttribute<string_type,_altova_mi_xs_altova_CtopLevelAttribute_altova_default2, 0, 0> default2;	// default Cstring

	MemberAttribute<string_type,_altova_mi_xs_altova_CtopLevelAttribute_altova_fixed, 0, 0> fixed;	// fixed Cstring
	MemberAttribute<string_type,_altova_mi_xs_altova_CtopLevelAttribute_altova_form, 0, 2> form;	// form CformChoice
	MemberElement<CannotationType, _altova_mi_xs_altova_CtopLevelAttribute_altova_annotation> annotation;
	struct annotation { typedef Iterator<CannotationType> iterator; };
	MemberElement<xs::ClocalSimpleType, _altova_mi_xs_altova_CtopLevelAttribute_altova_simpleType> simpleType;
	struct simpleType { typedef Iterator<xs::ClocalSimpleType> iterator; };
	CMSD_EXPORT void SetXsiType();
};



} // namespace xs

}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CtopLevelAttribute
