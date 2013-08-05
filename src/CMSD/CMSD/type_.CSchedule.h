#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CSchedule
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CSchedule

#include "type_.CUniqueEntity.h"


namespace CMSD
{

class CSchedule : public ::CMSD::CUniqueEntity
{
public:
	CMSD_EXPORT CSchedule(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CSchedule(CSchedule const& init);
	void operator=(CSchedule const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CSchedule); }
	MemberElement<CCreationTimeType2, _altova_mi_altova_CSchedule_altova_CreationTime> CreationTime;
	struct CreationTime { typedef Iterator<CCreationTimeType2> iterator; };
	MemberElement<CStartTimeType3, _altova_mi_altova_CSchedule_altova_StartTime> StartTime;
	struct StartTime { typedef Iterator<CStartTimeType3> iterator; };
	MemberElement<CEndTimeType2, _altova_mi_altova_CSchedule_altova_EndTime> EndTime;
	struct EndTime { typedef Iterator<CEndTimeType2> iterator; };
	MemberElement<CScheduleItem, _altova_mi_altova_CSchedule_altova_ScheduleItem> ScheduleItem;
	struct ScheduleItem { typedef Iterator<CScheduleItem> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CSchedule
