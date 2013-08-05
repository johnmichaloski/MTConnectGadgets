#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CMaintenanceProcessType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CMaintenanceProcessType



namespace CMSD
{

class CMaintenanceProcessType : public TypeBase
{
public:
	CMSD_EXPORT CMaintenanceProcessType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CMaintenanceProcessType(CMaintenanceProcessType const& init);
	void operator=(CMaintenanceProcessType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CMaintenanceProcessType); }
	MemberElement<CMaintenanceProcess, _altova_mi_altova_CMaintenanceProcessType_altova_MaintenanceProcess> MaintenanceProcess;
	struct MaintenanceProcess { typedef Iterator<CMaintenanceProcess> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CMaintenanceProcessType
