#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CMaintenanceProcess
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CMaintenanceProcess

#include "type_.CLimitedUniqueEntity.h"


namespace CMSD
{

class CMaintenanceProcess : public ::CMSD::CLimitedUniqueEntity
{
public:
	CMSD_EXPORT CMaintenanceProcess(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CMaintenanceProcess(CMaintenanceProcess const& init);
	void operator=(CMaintenanceProcess const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CMaintenanceProcess); }
	MemberElement<CResourcesRequired, _altova_mi_altova_CMaintenanceProcess_altova_ResourcesRequired> ResourcesRequired;
	struct ResourcesRequired { typedef Iterator<CResourcesRequired> iterator; };
	MemberElement<CPartGroup, _altova_mi_altova_CMaintenanceProcess_altova_PartsConsumed> PartsConsumed;
	struct PartsConsumed { typedef Iterator<CPartGroup> iterator; };
	MemberElement<CDuration, _altova_mi_altova_CMaintenanceProcess_altova_SetupTime> SetupTime;
	struct SetupTime { typedef Iterator<CDuration> iterator; };
	MemberElement<CDuration, _altova_mi_altova_CMaintenanceProcess_altova_OperationTime> OperationTime;
	struct OperationTime { typedef Iterator<CDuration> iterator; };
	MemberElement<CRepetitionCountType, _altova_mi_altova_CMaintenanceProcess_altova_RepetitionCount> RepetitionCount;
	struct RepetitionCount { typedef Iterator<CRepetitionCountType> iterator; };
	MemberElement<CCostAllocationData, _altova_mi_altova_CMaintenanceProcess_altova_CostAllocationData> CostAllocationData;
	struct CostAllocationData { typedef Iterator<CCostAllocationData> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CMaintenanceProcess_altova_SpecialInstruction> SpecialInstruction;
	struct SpecialInstruction { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<CMaintenanceProcessConstraint, _altova_mi_altova_CMaintenanceProcess_altova_ProcessConstraint> ProcessConstraint;
	struct ProcessConstraint { typedef Iterator<CMaintenanceProcessConstraint> iterator; };
	MemberElement<CMaintenanceProcessGroup, _altova_mi_altova_CMaintenanceProcess_altova_SubProcessGroup> SubProcessGroup;
	struct SubProcessGroup { typedef Iterator<CMaintenanceProcessGroup> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CMaintenanceProcess
