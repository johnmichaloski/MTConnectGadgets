#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CallType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CallType



namespace CMSD
{

namespace xs
{	

class CallType : public TypeBase
{
public:
	CMSD_EXPORT CallType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CallType(CallType const& init);
	void operator=(CallType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_xs_altova_CallType); }

	MemberAttribute<string_type,_altova_mi_xs_altova_CallType_altova_id, 0, 0> id;	// id CID

	MemberAttribute<string_type,_altova_mi_xs_altova_CallType_altova_name, 0, 0> name;	// name CNCName

	MemberAttribute<string_type,_altova_mi_xs_altova_CallType_altova_ref, 0, 0> ref;	// ref CQName
	MemberAttribute<unsigned __int64,_altova_mi_xs_altova_CallType_altova_minOccurs, 0, 2> minOccurs;	// minOccurs CminOccursType
	MemberAttribute<string_type,_altova_mi_xs_altova_CallType_altova_maxOccurs, 1, 1> maxOccurs;	// maxOccurs CmaxOccursType
	MemberElement<CannotationType, _altova_mi_xs_altova_CallType_altova_annotation> annotation;
	struct annotation { typedef Iterator<CannotationType> iterator; };
	MemberElement<xs::CnarrowMaxMin, _altova_mi_xs_altova_CallType_altova_element> element;
	struct element { typedef Iterator<xs::CnarrowMaxMin> iterator; };
	MemberElement<xs::CgroupRef, _altova_mi_xs_altova_CallType_altova_group> group;
	struct group { typedef Iterator<xs::CgroupRef> iterator; };
	MemberElement<xs::Call, _altova_mi_xs_altova_CallType_altova_all> all;
	struct all { typedef Iterator<xs::Call> iterator; };
	MemberElement<xs::CexplicitGroup, _altova_mi_xs_altova_CallType_altova_choice> choice;
	struct choice { typedef Iterator<xs::CexplicitGroup> iterator; };
	MemberElement<xs::CexplicitGroup, _altova_mi_xs_altova_CallType_altova_sequence> sequence;
	struct sequence { typedef Iterator<xs::CexplicitGroup> iterator; };
	MemberElement<CanyType, _altova_mi_xs_altova_CallType_altova_any> any;
	struct any { typedef Iterator<CanyType> iterator; };
};



} // namespace xs

}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CallType
