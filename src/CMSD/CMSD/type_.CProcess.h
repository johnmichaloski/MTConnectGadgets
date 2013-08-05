#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CProcess
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CProcess

#include "type_.CLimitedUniqueEntity.h"


namespace CMSD
{

class CProcess : public ::CMSD::CLimitedUniqueEntity
{
public:
	CMSD_EXPORT CProcess(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CProcess(CProcess const& init);
	void operator=(CProcess const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CProcess); }
	MemberElement<CPartGroup, _altova_mi_altova_CProcess_altova_PartsProduced> PartsProduced;
	struct PartsProduced { typedef Iterator<CPartGroup> iterator; };
	MemberElement<CPartGroup, _altova_mi_altova_CProcess_altova_PartsConsumed> PartsConsumed;
	struct PartsConsumed { typedef Iterator<CPartGroup> iterator; };
	MemberElement<CResourcesRequired, _altova_mi_altova_CProcess_altova_ResourcesRequired> ResourcesRequired;
	struct ResourcesRequired { typedef Iterator<CResourcesRequired> iterator; };
	MemberElement<CMachineProgramData, _altova_mi_altova_CProcess_altova_MachineProgramInformation> MachineProgramInformation;
	struct MachineProgramInformation { typedef Iterator<CMachineProgramData> iterator; };
	MemberElement<CDuration, _altova_mi_altova_CProcess_altova_SetupTime> SetupTime;
	struct SetupTime { typedef Iterator<CDuration> iterator; };
	MemberElement<CDuration, _altova_mi_altova_CProcess_altova_OperationTime> OperationTime;
	struct OperationTime { typedef Iterator<CDuration> iterator; };
	MemberElement<CRepetitionCountType2, _altova_mi_altova_CProcess_altova_RepetitionCount> RepetitionCount;
	struct RepetitionCount { typedef Iterator<CRepetitionCountType2> iterator; };
	MemberElement<CCostAllocationData, _altova_mi_altova_CProcess_altova_CostAllocationData> CostAllocationData;
	struct CostAllocationData { typedef Iterator<CCostAllocationData> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CProcess_altova_SpecialInstruction> SpecialInstruction;
	struct SpecialInstruction { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<CProcessConstraint, _altova_mi_altova_CProcess_altova_ProcessConstraint> ProcessConstraint;
	struct ProcessConstraint { typedef Iterator<CProcessConstraint> iterator; };
	MemberElement<CProcessGroup, _altova_mi_altova_CProcess_altova_SubProcessGroup> SubProcessGroup;
	struct SubProcessGroup { typedef Iterator<CProcessGroup> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CProcess
