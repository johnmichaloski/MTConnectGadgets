#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CnamedGroup
#define _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CnamedGroup



namespace CMSD
{

namespace xs
{	

class CnamedGroup : public TypeBase
{
public:
	CMSD_EXPORT CnamedGroup(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CnamedGroup(CnamedGroup const& init);
	void operator=(CnamedGroup const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_xs_altova_CnamedGroup); }

	MemberAttribute<string_type,_altova_mi_xs_altova_CnamedGroup_altova_id, 0, 0> id;	// id CID

	MemberAttribute<string_type,_altova_mi_xs_altova_CnamedGroup_altova_name, 0, 0> name;	// name CNCName

	MemberAttribute<string_type,_altova_mi_xs_altova_CnamedGroup_altova_ref, 0, 0> ref;	// ref CQName

	MemberAttribute<unsigned __int64,_altova_mi_xs_altova_CnamedGroup_altova_minOccurs, 0, 0> minOccurs;	// minOccurs CnonNegativeInteger
	MemberAttribute<string_type,_altova_mi_xs_altova_CnamedGroup_altova_maxOccurs, 1, 1> maxOccurs;	// maxOccurs CallNNI
	MemberElement<CannotationType, _altova_mi_xs_altova_CnamedGroup_altova_annotation> annotation;
	struct annotation { typedef Iterator<CannotationType> iterator; };
	MemberElement<xs::ClocalElement, _altova_mi_xs_altova_CnamedGroup_altova_element> element;
	struct element { typedef Iterator<xs::ClocalElement> iterator; };
	MemberElement<xs::CgroupRef, _altova_mi_xs_altova_CnamedGroup_altova_group> group;
	struct group { typedef Iterator<xs::CgroupRef> iterator; };
	MemberElement<xs::CallType, _altova_mi_xs_altova_CnamedGroup_altova_all> all;
	struct all { typedef Iterator<xs::CallType> iterator; };
	MemberElement<xs::CsimpleExplicitGroup, _altova_mi_xs_altova_CnamedGroup_altova_choice> choice;
	struct choice { typedef Iterator<xs::CsimpleExplicitGroup> iterator; };
	MemberElement<xs::CsimpleExplicitGroup, _altova_mi_xs_altova_CnamedGroup_altova_sequence> sequence;
	struct sequence { typedef Iterator<xs::CsimpleExplicitGroup> iterator; };
	MemberElement<CanyType, _altova_mi_xs_altova_CnamedGroup_altova_any> any;
	struct any { typedef Iterator<CanyType> iterator; };
	CMSD_EXPORT void SetXsiType();
};



} // namespace xs

}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CnamedGroup
