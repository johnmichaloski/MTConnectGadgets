#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CtopLevelSimpleType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CtopLevelSimpleType



namespace CMSD
{

namespace xs
{	

class CtopLevelSimpleType : public TypeBase
{
public:
	CMSD_EXPORT CtopLevelSimpleType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CtopLevelSimpleType(CtopLevelSimpleType const& init);
	void operator=(CtopLevelSimpleType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_xs_altova_CtopLevelSimpleType); }

	MemberAttribute<string_type,_altova_mi_xs_altova_CtopLevelSimpleType_altova_id, 0, 0> id;	// id CID
	MemberAttribute<string_type,_altova_mi_xs_altova_CtopLevelSimpleType_altova_final, 1, 4> final;	// final CsimpleDerivationSet

	MemberAttribute<string_type,_altova_mi_xs_altova_CtopLevelSimpleType_altova_name, 0, 0> name;	// name CNCName
	MemberElement<CannotationType, _altova_mi_xs_altova_CtopLevelSimpleType_altova_annotation> annotation;
	struct annotation { typedef Iterator<CannotationType> iterator; };
	MemberElement<CrestrictionType, _altova_mi_xs_altova_CtopLevelSimpleType_altova_restriction> restriction;
	struct restriction { typedef Iterator<CrestrictionType> iterator; };
	MemberElement<ClistType, _altova_mi_xs_altova_CtopLevelSimpleType_altova_list> list;
	struct list { typedef Iterator<ClistType> iterator; };
	MemberElement<CunionType, _altova_mi_xs_altova_CtopLevelSimpleType_altova_union2> union2;
	struct union2 { typedef Iterator<CunionType> iterator; };
	CMSD_EXPORT void SetXsiType();
};



} // namespace xs

}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CtopLevelSimpleType
