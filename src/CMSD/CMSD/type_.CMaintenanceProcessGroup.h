#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CMaintenanceProcessGroup
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CMaintenanceProcessGroup

#include "type_.CNotifyPropertyChangeBase.h"


namespace CMSD
{

class CMaintenanceProcessGroup : public ::CMSD::CNotifyPropertyChangeBase
{
public:
	CMSD_EXPORT CMaintenanceProcessGroup(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CMaintenanceProcessGroup(CMaintenanceProcessGroup const& init);
	void operator=(CMaintenanceProcessGroup const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CMaintenanceProcessGroup); }
	MemberElement<CProcessGroupTypeType, _altova_mi_altova_CMaintenanceProcessGroup_altova_Type> Type;
	struct Type { typedef Iterator<CProcessGroupTypeType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CMaintenanceProcessGroup_altova_DecisionText> DecisionText;
	struct DecisionText { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<CMaintenanceProcessReference, _altova_mi_altova_CMaintenanceProcessGroup_altova_Process> Process;
	struct Process { typedef Iterator<CMaintenanceProcessReference> iterator; };
	MemberElement<CMaintenanceProcessConstraint, _altova_mi_altova_CMaintenanceProcessGroup_altova_ProcessConstraint> ProcessConstraint;
	struct ProcessConstraint { typedef Iterator<CMaintenanceProcessConstraint> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CMaintenanceProcessGroup
