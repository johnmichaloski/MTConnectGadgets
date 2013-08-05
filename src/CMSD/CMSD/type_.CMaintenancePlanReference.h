#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CMaintenancePlanReference
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CMaintenancePlanReference

#include "type_.CAbstractEntityReference.h"


namespace CMSD
{

class CMaintenancePlanReference : public ::CMSD::CAbstractEntityReference
{
public:
	CMSD_EXPORT CMaintenancePlanReference(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CMaintenancePlanReference(CMaintenancePlanReference const& init);
	void operator=(CMaintenancePlanReference const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CMaintenancePlanReference); }
	MemberElement<xs::CstringType, _altova_mi_altova_CMaintenancePlanReference_altova_MaintenancePlanIdentifier> MaintenancePlanIdentifier;
	struct MaintenancePlanIdentifier { typedef Iterator<xs::CstringType> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CMaintenancePlanReference
