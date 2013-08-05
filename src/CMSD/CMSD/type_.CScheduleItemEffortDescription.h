#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CScheduleItemEffortDescription
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CScheduleItemEffortDescription

#include "type_.CNotifyPropertyChangeBase.h"


namespace CMSD
{

class CScheduleItemEffortDescription : public ::CMSD::CNotifyPropertyChangeBase
{
public:
	CMSD_EXPORT CScheduleItemEffortDescription(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CScheduleItemEffortDescription(CScheduleItemEffortDescription const& init);
	void operator=(CScheduleItemEffortDescription const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CScheduleItemEffortDescription); }
	MemberElement<CUpdateTimeType5, _altova_mi_altova_CScheduleItemEffortDescription_altova_UpdateTime> UpdateTime;
	struct UpdateTime { typedef Iterator<CUpdateTimeType5> iterator; };
	MemberElement<CStartTimeType4, _altova_mi_altova_CScheduleItemEffortDescription_altova_StartTime> StartTime;
	struct StartTime { typedef Iterator<CStartTimeType4> iterator; };
	MemberElement<CEndTimeType3, _altova_mi_altova_CScheduleItemEffortDescription_altova_EndTime> EndTime;
	struct EndTime { typedef Iterator<CEndTimeType3> iterator; };
	MemberElement<CDuration, _altova_mi_altova_CScheduleItemEffortDescription_altova_ProcessingTime> ProcessingTime;
	struct ProcessingTime { typedef Iterator<CDuration> iterator; };
	MemberElement<CResourcesRequired, _altova_mi_altova_CScheduleItemEffortDescription_altova_ResourcesUsed> ResourcesUsed;
	struct ResourcesUsed { typedef Iterator<CResourcesRequired> iterator; };
	MemberElement<CPartGroup, _altova_mi_altova_CScheduleItemEffortDescription_altova_PartsUsed> PartsUsed;
	struct PartsUsed { typedef Iterator<CPartGroup> iterator; };
	MemberElement<CPartGroup, _altova_mi_altova_CScheduleItemEffortDescription_altova_PartsProduced> PartsProduced;
	struct PartsProduced { typedef Iterator<CPartGroup> iterator; };
	MemberElement<CProperty, _altova_mi_altova_CScheduleItemEffortDescription_altova_Property> Property;
	struct Property { typedef Iterator<CProperty> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CScheduleItemEffortDescription
