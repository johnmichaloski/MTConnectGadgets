#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCalendarReference
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCalendarReference

#include "type_.CAbstractEntityReference.h"


namespace CMSD
{

class CCalendarReference : public ::CMSD::CAbstractEntityReference
{
public:
	CMSD_EXPORT CCalendarReference(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CCalendarReference(CCalendarReference const& init);
	void operator=(CCalendarReference const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CCalendarReference); }
	MemberElement<xs::CstringType, _altova_mi_altova_CCalendarReference_altova_CalendarIdentifier> CalendarIdentifier;
	struct CalendarIdentifier { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CCalendarReference_altova_ShiftScheduleIdentifier> ShiftScheduleIdentifier;
	struct ShiftScheduleIdentifier { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CCalendarReference_altova_ShiftIdentifier> ShiftIdentifier;
	struct ShiftIdentifier { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CCalendarReference_altova_HolidayIdentifier> HolidayIdentifier;
	struct HolidayIdentifier { typedef Iterator<xs::CstringType> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCalendarReference
