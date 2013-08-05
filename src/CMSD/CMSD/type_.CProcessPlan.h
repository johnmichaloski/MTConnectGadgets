#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CProcessPlan
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CProcessPlan

#include "type_.CUniqueEntity.h"


namespace CMSD
{

class CProcessPlan : public ::CMSD::CUniqueEntity
{
public:
	CMSD_EXPORT CProcessPlan(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CProcessPlan(CProcessPlan const& init);
	void operator=(CProcessPlan const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CProcessPlan); }
	MemberElement<CPartGroup, _altova_mi_altova_CProcessPlan_altova_PartsProduced> PartsProduced;
	struct PartsProduced { typedef Iterator<CPartGroup> iterator; };
	MemberElement<CPartGroup, _altova_mi_altova_CProcessPlan_altova_PartsConsumed> PartsConsumed;
	struct PartsConsumed { typedef Iterator<CPartGroup> iterator; };
	MemberElement<CResourcesRequired, _altova_mi_altova_CProcessPlan_altova_ResourcesRequired> ResourcesRequired;
	struct ResourcesRequired { typedef Iterator<CResourcesRequired> iterator; };
	MemberElement<CCostAllocationData, _altova_mi_altova_CProcessPlan_altova_CostAllocationData> CostAllocationData;
	struct CostAllocationData { typedef Iterator<CCostAllocationData> iterator; };
	MemberElement<CProcessReference, _altova_mi_altova_CProcessPlan_altova_FirstProcess> FirstProcess;
	struct FirstProcess { typedef Iterator<CProcessReference> iterator; };
	MemberElement<CProcess, _altova_mi_altova_CProcessPlan_altova_Process> Process;
	struct Process { typedef Iterator<CProcess> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CProcessPlan
