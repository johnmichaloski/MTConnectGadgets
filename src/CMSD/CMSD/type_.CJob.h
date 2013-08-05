#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CJob
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CJob

#include "type_.CUniqueEntity.h"


namespace CMSD
{

class CJob : public ::CMSD::CUniqueEntity
{
public:
	CMSD_EXPORT CJob(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CJob(CJob const& init);
	void operator=(CJob const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CJob); }
	MemberElement<CJobStatusType, _altova_mi_altova_CJob_altova_Status> Status;
	struct Status { typedef Iterator<CJobStatusType> iterator; };
	MemberElement<CUpdateTimeType, _altova_mi_altova_CJob_altova_UpdateTime> UpdateTime;
	struct UpdateTime { typedef Iterator<CUpdateTimeType> iterator; };
	MemberElement<CContactInformation, _altova_mi_altova_CJob_altova_RequestingParty> RequestingParty;
	struct RequestingParty { typedef Iterator<CContactInformation> iterator; };
	MemberElement<CContactInformation, _altova_mi_altova_CJob_altova_PerformingParty> PerformingParty;
	struct PerformingParty { typedef Iterator<CContactInformation> iterator; };
	MemberElement<COrderInformationReference, _altova_mi_altova_CJob_altova_AssociatedOrder> AssociatedOrder;
	struct AssociatedOrder { typedef Iterator<COrderInformationReference> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CJob_altova_Priority> Priority;
	struct Priority { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<CJobConstraint, _altova_mi_altova_CJob_altova_PrecedenceConstraint> PrecedenceConstraint;
	struct PrecedenceConstraint { typedef Iterator<CJobConstraint> iterator; };
	MemberElement<CJobReference, _altova_mi_altova_CJob_altova_SubJob> SubJob;
	struct SubJob { typedef Iterator<CJobReference> iterator; };
	MemberElement<CJobEffortDescription, _altova_mi_altova_CJob_altova_PlannedEffort> PlannedEffort;
	struct PlannedEffort { typedef Iterator<CJobEffortDescription> iterator; };
	MemberElement<CJobEffortDescription, _altova_mi_altova_CJob_altova_ActualEffort> ActualEffort;
	struct ActualEffort { typedef Iterator<CJobEffortDescription> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CJob
