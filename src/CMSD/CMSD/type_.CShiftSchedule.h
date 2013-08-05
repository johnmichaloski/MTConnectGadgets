#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CShiftSchedule
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CShiftSchedule

#include "type_.CLimitedUniqueEntity.h"


namespace CMSD
{

class CShiftSchedule : public ::CMSD::CLimitedUniqueEntity
{
public:
	CMSD_EXPORT CShiftSchedule(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CShiftSchedule(CShiftSchedule const& init);
	void operator=(CShiftSchedule const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CShiftSchedule); }
	MemberElement<CEffectiveStartDateType2, _altova_mi_altova_CShiftSchedule_altova_EffectiveStartDate> EffectiveStartDate;
	struct EffectiveStartDate { typedef Iterator<CEffectiveStartDateType2> iterator; };
	MemberElement<CEffectiveEndDateType2, _altova_mi_altova_CShiftSchedule_altova_EffectiveEndDate> EffectiveEndDate;
	struct EffectiveEndDate { typedef Iterator<CEffectiveEndDateType2> iterator; };
	MemberElement<CCalendarReference, _altova_mi_altova_CShiftSchedule_altova_ApplicableShift> ApplicableShift;
	struct ApplicableShift { typedef Iterator<CCalendarReference> iterator; };
	MemberElement<CCalendarReference, _altova_mi_altova_CShiftSchedule_altova_ApplicableHoliday> ApplicableHoliday;
	struct ApplicableHoliday { typedef Iterator<CCalendarReference> iterator; };
	MemberElement<CAvailabilityException, _altova_mi_altova_CShiftSchedule_altova_AvailabilityException> AvailabilityException;
	struct AvailabilityException { typedef Iterator<CAvailabilityException> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CShiftSchedule
