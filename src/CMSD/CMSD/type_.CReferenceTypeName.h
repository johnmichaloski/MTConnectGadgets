#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CReferenceTypeName
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CReferenceTypeName



namespace CMSD
{

class CReferenceTypeName : public TypeBase
{
public:
	CMSD_EXPORT CReferenceTypeName(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CReferenceTypeName(CReferenceTypeName const& init);
	void operator=(CReferenceTypeName const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_altova_CReferenceTypeName); }

	enum EnumValues {
		Invalid = -1,
		k_BillOfMaterialsComponentReference = 0, // BillOfMaterialsComponentReference
		k_BillOfMaterialsReference = 1, // BillOfMaterialsReference
		k_CalendarReference = 2, // CalendarReference
		k_DistributionDefinitionReference = 3, // DistributionDefinitionReference
		k_InventoryItemClassReference = 4, // InventoryItemClassReference
		k_InventoryItemReference = 5, // InventoryItemReference
		k_JobReference = 6, // JobReference
		k_LayoutElementReference = 7, // LayoutElementReference
		k_MaintenancePlanReference = 8, // MaintenancePlanReference
		k_MaintenanceProcessReference = 9, // MaintenanceProcessReference
		k_OrderInformationReference = 10, // OrderInformationReference
		k_PartReference = 11, // PartReference
		k_PartTypeReference = 12, // PartTypeReference
		k_ProcessPlanReference = 13, // ProcessPlanReference
		k_ProcessReference = 14, // ProcessReference
		k_ReferenceMaterialReference = 15, // ReferenceMaterialReference
		k_ResourceClassReference = 16, // ResourceClassReference
		k_ResourceReference = 17, // ResourceReference
		k_ScheduleInformationReference = 18, // ScheduleInformationReference
		k_SetupChangeoverReference = 19, // SetupChangeoverReference
		k_SetupDefinitionReference = 20, // SetupDefinitionReference
		k_SkillReference = 21, // SkillReference
		EnumValueCount
	};
	void operator= (const string_type& value) 
	{
		altova::XmlFormatter* Formatter = static_cast<altova::XmlFormatter*>(altova::AnySimpleTypeFormatter);
		MsxmlTreeOperations::SetValue(GetNode(), Formatter->Format(value));
	}	
		
	operator string_type()
	{
		return CastAs<string_type >::Do(GetNode(), 0);
	}
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CReferenceTypeName
