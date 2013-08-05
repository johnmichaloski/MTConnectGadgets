#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_Call
#define _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_Call



namespace CMSD
{

namespace xs
{	

class Call : public TypeBase
{
public:
	CMSD_EXPORT Call(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT Call(Call const& init);
	void operator=(Call const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_xs_altova_Call); }

	MemberAttribute<string_type,_altova_mi_xs_altova_Call_altova_id, 0, 0> id;	// id CID

	MemberAttribute<string_type,_altova_mi_xs_altova_Call_altova_name, 0, 0> name;	// name CNCName

	MemberAttribute<string_type,_altova_mi_xs_altova_Call_altova_ref, 0, 0> ref;	// ref CQName
	MemberAttribute<unsigned __int64,_altova_mi_xs_altova_Call_altova_minOccurs, 0, 2> minOccurs;	// minOccurs CminOccursType
	MemberAttribute<string_type,_altova_mi_xs_altova_Call_altova_maxOccurs, 1, 1> maxOccurs;	// maxOccurs CmaxOccursType
	MemberElement<CannotationType, _altova_mi_xs_altova_Call_altova_annotation> annotation;
	struct annotation { typedef Iterator<CannotationType> iterator; };
	MemberElement<xs::CnarrowMaxMin, _altova_mi_xs_altova_Call_altova_element> element;
	struct element { typedef Iterator<xs::CnarrowMaxMin> iterator; };
	MemberElement<xs::CgroupRef, _altova_mi_xs_altova_Call_altova_group> group;
	struct group { typedef Iterator<xs::CgroupRef> iterator; };
	MemberElement<xs::Call, _altova_mi_xs_altova_Call_altova_all> all;
	struct all { typedef Iterator<xs::Call> iterator; };
	MemberElement<xs::CexplicitGroup, _altova_mi_xs_altova_Call_altova_choice> choice;
	struct choice { typedef Iterator<xs::CexplicitGroup> iterator; };
	MemberElement<xs::CexplicitGroup, _altova_mi_xs_altova_Call_altova_sequence> sequence;
	struct sequence { typedef Iterator<xs::CexplicitGroup> iterator; };
	MemberElement<CanyType, _altova_mi_xs_altova_Call_altova_any> any;
	struct any { typedef Iterator<CanyType> iterator; };
	CMSD_EXPORT void SetXsiType();
};



} // namespace xs

}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_Call
