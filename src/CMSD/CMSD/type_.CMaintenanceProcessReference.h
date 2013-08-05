#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CMaintenanceProcessReference
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CMaintenanceProcessReference

#include "type_.CAbstractEntityReference.h"


namespace CMSD
{

class CMaintenanceProcessReference : public ::CMSD::CAbstractEntityReference
{
public:
	CMSD_EXPORT CMaintenanceProcessReference(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CMaintenanceProcessReference(CMaintenanceProcessReference const& init);
	void operator=(CMaintenanceProcessReference const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CMaintenanceProcessReference); }
	MemberElement<xs::CstringType, _altova_mi_altova_CMaintenanceProcessReference_altova_MaintenancePlanIdentifier> MaintenancePlanIdentifier;
	struct MaintenancePlanIdentifier { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CMaintenanceProcessReference_altova_MaintenanceProcessIdentifier> MaintenanceProcessIdentifier;
	struct MaintenanceProcessIdentifier { typedef Iterator<xs::CstringType> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CMaintenanceProcessReference
