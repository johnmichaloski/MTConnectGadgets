#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_Cgroup
#define _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_Cgroup

#include "type_xs.Cannotated.h"


namespace CMSD
{

namespace xs
{	

class Cgroup : public ::CMSD::xs::Cannotated
{
public:
	CMSD_EXPORT Cgroup(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT Cgroup(Cgroup const& init);
	void operator=(Cgroup const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_xs_altova_Cgroup); }

	MemberAttribute<string_type,_altova_mi_xs_altova_Cgroup_altova_name, 0, 0> name;	// name CNCName

	MemberAttribute<string_type,_altova_mi_xs_altova_Cgroup_altova_ref, 0, 0> ref;	// ref CQName

	MemberAttribute<unsigned __int64,_altova_mi_xs_altova_Cgroup_altova_minOccurs, 0, 0> minOccurs;	// minOccurs CnonNegativeInteger
	MemberAttribute<string_type,_altova_mi_xs_altova_Cgroup_altova_maxOccurs, 1, 1> maxOccurs;	// maxOccurs CallNNI
	MemberElement<xs::ClocalElement, _altova_mi_xs_altova_Cgroup_altova_element> element;
	struct element { typedef Iterator<xs::ClocalElement> iterator; };
	MemberElement<xs::CgroupRef, _altova_mi_xs_altova_Cgroup_altova_group> group;
	struct group { typedef Iterator<xs::CgroupRef> iterator; };
	MemberElement<xs::Call, _altova_mi_xs_altova_Cgroup_altova_all> all;
	struct all { typedef Iterator<xs::Call> iterator; };
	MemberElement<xs::CexplicitGroup, _altova_mi_xs_altova_Cgroup_altova_choice> choice;
	struct choice { typedef Iterator<xs::CexplicitGroup> iterator; };
	MemberElement<xs::CexplicitGroup, _altova_mi_xs_altova_Cgroup_altova_sequence> sequence;
	struct sequence { typedef Iterator<xs::CexplicitGroup> iterator; };
	MemberElement<CanyType, _altova_mi_xs_altova_Cgroup_altova_any> any;
	struct any { typedef Iterator<CanyType> iterator; };
	CMSD_EXPORT void SetXsiType();
};



} // namespace xs

}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_Cgroup
