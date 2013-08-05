#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CUniqueEntityTypeType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CUniqueEntityTypeType



namespace CMSD
{

class CUniqueEntityTypeType : public TypeBase
{
public:
	CMSD_EXPORT CUniqueEntityTypeType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CUniqueEntityTypeType(CUniqueEntityTypeType const& init);
	void operator=(CUniqueEntityTypeType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CUniqueEntityTypeType); }

	enum EnumValues {
		Invalid = -1,
		k_Layout = 0, // Layout
		k_LayoutObject = 1, // LayoutObject
		k_Part = 2, // Part
		k_PartType = 3, // PartType
		k_BillOfMaterials = 4, // BillOfMaterials
		k_InventoryItem = 5, // InventoryItem
		k_InventoryItemClass = 6, // InventoryItemClass
		k_Order = 7, // Order
		k_Job = 8, // Job
		k_Schedule = 9, // Schedule
		k_Calendar = 10, // Calendar
		k_ProcessPlan = 11, // ProcessPlan
		k_MaintenancePlan = 12, // MaintenancePlan
		k_Resource = 13, // Resource
		k_ResourceClass = 14, // ResourceClass
		k_SkillDefinition = 15, // SkillDefinition
		k_SetupDefinition = 16, // SetupDefinition
		k_SetupChangeoverDefinition = 17, // SetupChangeoverDefinition
		k_ReferenceMaterial = 18, // ReferenceMaterial
		k_DistributionDefinition = 19, // DistributionDefinition
		EnumValueCount
	};

	
	CMSD_EXPORT int GetEnumerationValue();
	CMSD_EXPORT void SetEnumerationValue( const int index);
	CMSD_EXPORT void operator=(const string_type& value);
	CMSD_EXPORT operator string_type();
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CUniqueEntityTypeType