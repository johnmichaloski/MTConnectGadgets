#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCalendar
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCalendar

#include "type_.CUniqueEntity.h"


namespace CMSD
{

class CCalendar : public ::CMSD::CUniqueEntity
{
public:
	CMSD_EXPORT CCalendar(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CCalendar(CCalendar const& init);
	void operator=(CCalendar const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CCalendar); }
	MemberElement<CEffectiveStartDateType, _altova_mi_altova_CCalendar_altova_EffectiveStartDate> EffectiveStartDate;
	struct EffectiveStartDate { typedef Iterator<CEffectiveStartDateType> iterator; };
	MemberElement<CEffectiveEndDateType, _altova_mi_altova_CCalendar_altova_EffectiveEndDate> EffectiveEndDate;
	struct EffectiveEndDate { typedef Iterator<CEffectiveEndDateType> iterator; };
	MemberElement<CHoliday, _altova_mi_altova_CCalendar_altova_Holiday> Holiday;
	struct Holiday { typedef Iterator<CHoliday> iterator; };
	MemberElement<CShift, _altova_mi_altova_CCalendar_altova_Shift> Shift;
	struct Shift { typedef Iterator<CShift> iterator; };
	MemberElement<CShiftSchedule, _altova_mi_altova_CCalendar_altova_ShiftSchedule> ShiftSchedule;
	struct ShiftSchedule { typedef Iterator<CShiftSchedule> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCalendar
