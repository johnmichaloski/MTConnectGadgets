#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CMaintenanceProcessConstraint
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CMaintenanceProcessConstraint

#include "type_.CPrecedenceConstraint.h"


namespace CMSD
{

class CMaintenanceProcessConstraint : public ::CMSD::CPrecedenceConstraint
{
public:
	CMSD_EXPORT CMaintenanceProcessConstraint(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CMaintenanceProcessConstraint(CMaintenanceProcessConstraint const& init);
	void operator=(CMaintenanceProcessConstraint const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CMaintenanceProcessConstraint); }
	MemberElement<CMaintenanceProcessReference, _altova_mi_altova_CMaintenanceProcessConstraint_altova_PredecessorProcess> PredecessorProcess;
	struct PredecessorProcess { typedef Iterator<CMaintenanceProcessReference> iterator; };
	MemberElement<CMaintenanceProcessReference, _altova_mi_altova_CMaintenanceProcessConstraint_altova_SuccessorProcess> SuccessorProcess;
	struct SuccessorProcess { typedef Iterator<CMaintenanceProcessReference> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CMaintenanceProcessConstraint
