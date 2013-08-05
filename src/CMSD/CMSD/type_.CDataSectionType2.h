#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CDataSectionType2
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CDataSectionType2



namespace CMSD
{

class CDataSectionType2 : public TypeBase
{
public:
	CMSD_EXPORT CDataSectionType2(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CDataSectionType2(CDataSectionType2 const& init);
	void operator=(CDataSectionType2 const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CDataSectionType2); }
	MemberElement<CPart, _altova_mi_altova_CDataSectionType2_altova_Part> Part;
	struct Part { typedef Iterator<CPart> iterator; };
	MemberElement<CResourceClass, _altova_mi_altova_CDataSectionType2_altova_ResourceClass> ResourceClass;
	struct ResourceClass { typedef Iterator<CResourceClass> iterator; };
	MemberElement<CPartType, _altova_mi_altova_CDataSectionType2_altova_PartType> PartType;
	struct PartType { typedef Iterator<CPartType> iterator; };
	MemberElement<CDistributionDefinition, _altova_mi_altova_CDataSectionType2_altova_DistributionDefinition> DistributionDefinition;
	struct DistributionDefinition { typedef Iterator<CDistributionDefinition> iterator; };
	MemberElement<CCalendar, _altova_mi_altova_CDataSectionType2_altova_Calendar> Calendar;
	struct Calendar { typedef Iterator<CCalendar> iterator; };
	MemberElement<CLayout, _altova_mi_altova_CDataSectionType2_altova_Layout> Layout;
	struct Layout { typedef Iterator<CLayout> iterator; };
	MemberElement<CResource, _altova_mi_altova_CDataSectionType2_altova_Resource> Resource;
	struct Resource { typedef Iterator<CResource> iterator; };
	MemberElement<CInventoryItem, _altova_mi_altova_CDataSectionType2_altova_InventoryItem> InventoryItem;
	struct InventoryItem { typedef Iterator<CInventoryItem> iterator; };
	MemberElement<CSkillDefinition, _altova_mi_altova_CDataSectionType2_altova_SkillDefinition> SkillDefinition;
	struct SkillDefinition { typedef Iterator<CSkillDefinition> iterator; };
	MemberElement<CMaintenancePlan, _altova_mi_altova_CDataSectionType2_altova_MaintenancePlan> MaintenancePlan;
	struct MaintenancePlan { typedef Iterator<CMaintenancePlan> iterator; };
	MemberElement<CBillOfMaterials, _altova_mi_altova_CDataSectionType2_altova_BillOfMaterials> BillOfMaterials;
	struct BillOfMaterials { typedef Iterator<CBillOfMaterials> iterator; };
	MemberElement<CSetupDefinition, _altova_mi_altova_CDataSectionType2_altova_SetupDefinition> SetupDefinition;
	struct SetupDefinition { typedef Iterator<CSetupDefinition> iterator; };
	MemberElement<CJob, _altova_mi_altova_CDataSectionType2_altova_Job> Job;
	struct Job { typedef Iterator<CJob> iterator; };
	MemberElement<COrder, _altova_mi_altova_CDataSectionType2_altova_Order> Order;
	struct Order { typedef Iterator<COrder> iterator; };
	MemberElement<CSetupChangeoverDefinition, _altova_mi_altova_CDataSectionType2_altova_SetupChangeoverDefinition> SetupChangeoverDefinition;
	struct SetupChangeoverDefinition { typedef Iterator<CSetupChangeoverDefinition> iterator; };
	MemberElement<CLayoutObject, _altova_mi_altova_CDataSectionType2_altova_LayoutObject> LayoutObject;
	struct LayoutObject { typedef Iterator<CLayoutObject> iterator; };
	MemberElement<CProcessPlan, _altova_mi_altova_CDataSectionType2_altova_ProcessPlan> ProcessPlan;
	struct ProcessPlan { typedef Iterator<CProcessPlan> iterator; };
	MemberElement<CSchedule, _altova_mi_altova_CDataSectionType2_altova_Schedule> Schedule;
	struct Schedule { typedef Iterator<CSchedule> iterator; };
	MemberElement<CInventoryItemClass, _altova_mi_altova_CDataSectionType2_altova_InventoryItemClass> InventoryItemClass;
	struct InventoryItemClass { typedef Iterator<CInventoryItemClass> iterator; };
	MemberElement<CReferenceMaterial, _altova_mi_altova_CDataSectionType2_altova_ReferenceMaterial> ReferenceMaterial;
	struct ReferenceMaterial { typedef Iterator<CReferenceMaterial> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CDataSectionType2
