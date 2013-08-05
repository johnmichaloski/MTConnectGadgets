#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CProperty
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CProperty

#include "type_.CNotifyPropertyChangeBase.h"


namespace CMSD
{

class CProperty : public ::CMSD::CNotifyPropertyChangeBase
{
public:
	CMSD_EXPORT CProperty(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CProperty(CProperty const& init);
	void operator=(CProperty const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CProperty); }
	MemberElement<CPropertyDescriptionReference, _altova_mi_altova_CProperty_altova_PropertyDescription> PropertyDescription;
	struct PropertyDescription { typedef Iterator<CPropertyDescriptionReference> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CProperty_altova_Name> Name;
	struct Name { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CProperty_altova_Description> Description;
	struct Description { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CProperty_altova_Unit> Unit;
	struct Unit { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CProperty_altova_Value2> Value2;
	struct Value2 { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<CDistribution, _altova_mi_altova_CProperty_altova_Distribution> Distribution;
	struct Distribution { typedef Iterator<CDistribution> iterator; };
	MemberElement<CBillOfMaterialsComponentReference, _altova_mi_altova_CProperty_altova_BillOfMaterialsComponentReference> BillOfMaterialsComponentReference;
	struct BillOfMaterialsComponentReference { typedef Iterator<CBillOfMaterialsComponentReference> iterator; };
	MemberElement<CBillOfMaterialsReference, _altova_mi_altova_CProperty_altova_BillOfMaterialsReference> BillOfMaterialsReference;
	struct BillOfMaterialsReference { typedef Iterator<CBillOfMaterialsReference> iterator; };
	MemberElement<CCalendarReference, _altova_mi_altova_CProperty_altova_CalendarReference> CalendarReference;
	struct CalendarReference { typedef Iterator<CCalendarReference> iterator; };
	MemberElement<CDistributionDefinitionReference, _altova_mi_altova_CProperty_altova_DistributionDefinitionReference> DistributionDefinitionReference;
	struct DistributionDefinitionReference { typedef Iterator<CDistributionDefinitionReference> iterator; };
	MemberElement<CInventoryItemClassReference, _altova_mi_altova_CProperty_altova_InventoryItemClassReference> InventoryItemClassReference;
	struct InventoryItemClassReference { typedef Iterator<CInventoryItemClassReference> iterator; };
	MemberElement<CInventoryItemReference, _altova_mi_altova_CProperty_altova_InventoryItemReference> InventoryItemReference;
	struct InventoryItemReference { typedef Iterator<CInventoryItemReference> iterator; };
	MemberElement<CJobReference, _altova_mi_altova_CProperty_altova_JobReference> JobReference;
	struct JobReference { typedef Iterator<CJobReference> iterator; };
	MemberElement<CLayoutElementReference, _altova_mi_altova_CProperty_altova_LayoutElementReference> LayoutElementReference;
	struct LayoutElementReference { typedef Iterator<CLayoutElementReference> iterator; };
	MemberElement<CMaintenancePlanReference, _altova_mi_altova_CProperty_altova_MaintenancePlanReference> MaintenancePlanReference;
	struct MaintenancePlanReference { typedef Iterator<CMaintenancePlanReference> iterator; };
	MemberElement<CMaintenanceProcessReference, _altova_mi_altova_CProperty_altova_MaintenanceProcessReference> MaintenanceProcessReference;
	struct MaintenanceProcessReference { typedef Iterator<CMaintenanceProcessReference> iterator; };
	MemberElement<COrderInformationReference, _altova_mi_altova_CProperty_altova_OrderInformationReference> OrderInformationReference;
	struct OrderInformationReference { typedef Iterator<COrderInformationReference> iterator; };
	MemberElement<CPartReference, _altova_mi_altova_CProperty_altova_PartReference> PartReference;
	struct PartReference { typedef Iterator<CPartReference> iterator; };
	MemberElement<CPartTypeReference, _altova_mi_altova_CProperty_altova_PartTypeReference> PartTypeReference;
	struct PartTypeReference { typedef Iterator<CPartTypeReference> iterator; };
	MemberElement<CProcessPlanReference, _altova_mi_altova_CProperty_altova_ProcessPlanReference> ProcessPlanReference;
	struct ProcessPlanReference { typedef Iterator<CProcessPlanReference> iterator; };
	MemberElement<CProcessReference, _altova_mi_altova_CProperty_altova_ProcessReference> ProcessReference;
	struct ProcessReference { typedef Iterator<CProcessReference> iterator; };
	MemberElement<CPropertyDescriptionReference, _altova_mi_altova_CProperty_altova_PropertyDescriptionReference> PropertyDescriptionReference;
	struct PropertyDescriptionReference { typedef Iterator<CPropertyDescriptionReference> iterator; };
	MemberElement<CReferenceMaterialReference, _altova_mi_altova_CProperty_altova_ReferenceMaterialReference> ReferenceMaterialReference;
	struct ReferenceMaterialReference { typedef Iterator<CReferenceMaterialReference> iterator; };
	MemberElement<CResourceClassReference, _altova_mi_altova_CProperty_altova_ResourceClassReference> ResourceClassReference;
	struct ResourceClassReference { typedef Iterator<CResourceClassReference> iterator; };
	MemberElement<CResourceReference, _altova_mi_altova_CProperty_altova_ResourceReference> ResourceReference;
	struct ResourceReference { typedef Iterator<CResourceReference> iterator; };
	MemberElement<CScheduleInformationReference, _altova_mi_altova_CProperty_altova_ScheduleInformationReference> ScheduleInformationReference;
	struct ScheduleInformationReference { typedef Iterator<CScheduleInformationReference> iterator; };
	MemberElement<CSetupChangeoverReference, _altova_mi_altova_CProperty_altova_SetupChangeoverReference> SetupChangeoverReference;
	struct SetupChangeoverReference { typedef Iterator<CSetupChangeoverReference> iterator; };
	MemberElement<CSetupDefinitionReference, _altova_mi_altova_CProperty_altova_SetupDefinitionReference> SetupDefinitionReference;
	struct SetupDefinitionReference { typedef Iterator<CSetupDefinitionReference> iterator; };
	MemberElement<CSkillReference, _altova_mi_altova_CProperty_altova_SkillReference> SkillReference;
	struct SkillReference { typedef Iterator<CSkillReference> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CProperty
