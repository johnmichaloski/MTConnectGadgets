#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CScheduleInformationReference
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CScheduleInformationReference

#include "type_.CAbstractEntityReference.h"


namespace CMSD
{

class CScheduleInformationReference : public ::CMSD::CAbstractEntityReference
{
public:
	CMSD_EXPORT CScheduleInformationReference(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CScheduleInformationReference(CScheduleInformationReference const& init);
	void operator=(CScheduleInformationReference const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CScheduleInformationReference); }
	MemberElement<xs::CstringType, _altova_mi_altova_CScheduleInformationReference_altova_ScheduleIdentifier> ScheduleIdentifier;
	struct ScheduleIdentifier { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CScheduleInformationReference_altova_ScheduleItemIdentifier> ScheduleItemIdentifier;
	struct ScheduleItemIdentifier { typedef Iterator<xs::CstringType> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CScheduleInformationReference
