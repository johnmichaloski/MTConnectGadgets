#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CJobEffortDescription
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CJobEffortDescription

#include "type_.CNotifyPropertyChangeBase.h"


namespace CMSD
{

class CJobEffortDescription : public ::CMSD::CNotifyPropertyChangeBase
{
public:
	CMSD_EXPORT CJobEffortDescription(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CJobEffortDescription(CJobEffortDescription const& init);
	void operator=(CJobEffortDescription const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CJobEffortDescription); }
	MemberElement<CUpdateTimeType2, _altova_mi_altova_CJobEffortDescription_altova_UpdateTime> UpdateTime;
	struct UpdateTime { typedef Iterator<CUpdateTimeType2> iterator; };
	MemberElement<CPartGroup, _altova_mi_altova_CJobEffortDescription_altova_PartsProduced> PartsProduced;
	struct PartsProduced { typedef Iterator<CPartGroup> iterator; };
	MemberElement<CPartGroup, _altova_mi_altova_CJobEffortDescription_altova_PartsConsumed> PartsConsumed;
	struct PartsConsumed { typedef Iterator<CPartGroup> iterator; };
	MemberElement<CResourcesRequired, _altova_mi_altova_CJobEffortDescription_altova_ResourcesRequired> ResourcesRequired;
	struct ResourcesRequired { typedef Iterator<CResourcesRequired> iterator; };
	MemberElement<CDueDateType, _altova_mi_altova_CJobEffortDescription_altova_DueDate> DueDate;
	struct DueDate { typedef Iterator<CDueDateType> iterator; };
	MemberElement<CReleaseDateType, _altova_mi_altova_CJobEffortDescription_altova_ReleaseDate> ReleaseDate;
	struct ReleaseDate { typedef Iterator<CReleaseDateType> iterator; };
	MemberElement<CStartTimeType2, _altova_mi_altova_CJobEffortDescription_altova_StartTime> StartTime;
	struct StartTime { typedef Iterator<CStartTimeType2> iterator; };
	MemberElement<CEndTimeType, _altova_mi_altova_CJobEffortDescription_altova_EndTime> EndTime;
	struct EndTime { typedef Iterator<CEndTimeType> iterator; };
	MemberElement<CDuration, _altova_mi_altova_CJobEffortDescription_altova_SetupTime> SetupTime;
	struct SetupTime { typedef Iterator<CDuration> iterator; };
	MemberElement<CDuration, _altova_mi_altova_CJobEffortDescription_altova_ProcessingTime> ProcessingTime;
	struct ProcessingTime { typedef Iterator<CDuration> iterator; };
	MemberElement<CProcessPlanReference, _altova_mi_altova_CJobEffortDescription_altova_ProcessPlan> ProcessPlan;
	struct ProcessPlan { typedef Iterator<CProcessPlanReference> iterator; };
	MemberElement<CProcessReference, _altova_mi_altova_CJobEffortDescription_altova_CurrentProcessPlanStep> CurrentProcessPlanStep;
	struct CurrentProcessPlanStep { typedef Iterator<CProcessReference> iterator; };
	MemberElement<CMaintenancePlanReference, _altova_mi_altova_CJobEffortDescription_altova_MaintenancePlan> MaintenancePlan;
	struct MaintenancePlan { typedef Iterator<CMaintenancePlanReference> iterator; };
	MemberElement<CMaintenanceProcessReference, _altova_mi_altova_CJobEffortDescription_altova_CurrentMaintenancePlanStep> CurrentMaintenancePlanStep;
	struct CurrentMaintenancePlanStep { typedef Iterator<CMaintenanceProcessReference> iterator; };
	MemberElement<CCostAllocationData, _altova_mi_altova_CJobEffortDescription_altova_CostAllocationData> CostAllocationData;
	struct CostAllocationData { typedef Iterator<CCostAllocationData> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CJobEffortDescription_altova_Note> Note;
	struct Note { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<CEvent, _altova_mi_altova_CJobEffortDescription_altova_Event> Event;
	struct Event { typedef Iterator<CEvent> iterator; };
	MemberElement<CProperty, _altova_mi_altova_CJobEffortDescription_altova_Property> Property;
	struct Property { typedef Iterator<CProperty> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CJobEffortDescription
