#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CScheduleItem
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CScheduleItem

#include "type_.CLimitedUniqueEntity.h"


namespace CMSD
{

class CScheduleItem : public ::CMSD::CLimitedUniqueEntity
{
public:
	CMSD_EXPORT CScheduleItem(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CScheduleItem(CScheduleItem const& init);
	void operator=(CScheduleItem const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CScheduleItem); }
	MemberElement<CJobStatusType, _altova_mi_altova_CScheduleItem_altova_Status> Status;
	struct Status { typedef Iterator<CJobStatusType> iterator; };
	MemberElement<CJobReference, _altova_mi_altova_CScheduleItem_altova_AssociatedJob> AssociatedJob;
	struct AssociatedJob { typedef Iterator<CJobReference> iterator; };
	MemberElement<COrderInformationReference, _altova_mi_altova_CScheduleItem_altova_AssociatedOrderInformation> AssociatedOrderInformation;
	struct AssociatedOrderInformation { typedef Iterator<COrderInformationReference> iterator; };
	MemberElement<CProcessReference, _altova_mi_altova_CScheduleItem_altova_AssociatedProcess> AssociatedProcess;
	struct AssociatedProcess { typedef Iterator<CProcessReference> iterator; };
	MemberElement<CProcessPlanReference, _altova_mi_altova_CScheduleItem_altova_AssociatedProcessPlan> AssociatedProcessPlan;
	struct AssociatedProcessPlan { typedef Iterator<CProcessPlanReference> iterator; };
	MemberElement<CMaintenancePlanReference, _altova_mi_altova_CScheduleItem_altova_AssociatedMaintenancePlan> AssociatedMaintenancePlan;
	struct AssociatedMaintenancePlan { typedef Iterator<CMaintenancePlanReference> iterator; };
	MemberElement<CMaintenanceProcessReference, _altova_mi_altova_CScheduleItem_altova_AssociatedMaintenanceProcess> AssociatedMaintenanceProcess;
	struct AssociatedMaintenanceProcess { typedef Iterator<CMaintenanceProcessReference> iterator; };
	MemberElement<CScheduleItemEffortDescription, _altova_mi_altova_CScheduleItem_altova_PlannedEffort> PlannedEffort;
	struct PlannedEffort { typedef Iterator<CScheduleItemEffortDescription> iterator; };
	MemberElement<CScheduleItemEffortDescription, _altova_mi_altova_CScheduleItem_altova_ActualEffort> ActualEffort;
	struct ActualEffort { typedef Iterator<CScheduleItemEffortDescription> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CScheduleItem
