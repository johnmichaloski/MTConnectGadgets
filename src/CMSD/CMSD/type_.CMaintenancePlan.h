#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CMaintenancePlan
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CMaintenancePlan

#include "type_.CUniqueEntity.h"


namespace CMSD
{

class CMaintenancePlan : public ::CMSD::CUniqueEntity
{
public:
	CMSD_EXPORT CMaintenancePlan(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CMaintenancePlan(CMaintenancePlan const& init);
	void operator=(CMaintenancePlan const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CMaintenancePlan); }
	MemberElement<CResourceReference, _altova_mi_altova_CMaintenancePlan_altova_MaintainedResource> MaintainedResource;
	struct MaintainedResource { typedef Iterator<CResourceReference> iterator; };
	MemberElement<CDuration, _altova_mi_altova_CMaintenancePlan_altova_Periodicity> Periodicity;
	struct Periodicity { typedef Iterator<CDuration> iterator; };
	MemberElement<CCostAllocationData, _altova_mi_altova_CMaintenancePlan_altova_CostAllocationData> CostAllocationData;
	struct CostAllocationData { typedef Iterator<CCostAllocationData> iterator; };
	MemberElement<CMaintenanceProcessReference, _altova_mi_altova_CMaintenancePlan_altova_FirstProcess> FirstProcess;
	struct FirstProcess { typedef Iterator<CMaintenanceProcessReference> iterator; };
	MemberElement<CMaintenanceProcessType, _altova_mi_altova_CMaintenancePlan_altova_MaintenanceProcess> MaintenanceProcess;
	struct MaintenanceProcess { typedef Iterator<CMaintenanceProcessType> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CMaintenancePlan
