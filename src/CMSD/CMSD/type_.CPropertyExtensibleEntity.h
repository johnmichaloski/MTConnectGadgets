#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPropertyExtensibleEntity
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPropertyExtensibleEntity



namespace CMSD
{

class CPropertyExtensibleEntity : public TypeBase
{
public:
	CMSD_EXPORT CPropertyExtensibleEntity(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CPropertyExtensibleEntity(CPropertyExtensibleEntity const& init);
	void operator=(CPropertyExtensibleEntity const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_altova_CPropertyExtensibleEntity); }

	enum EnumValues {
		Invalid = -1,
		k_Layout = 0, // Layout
		k_LayoutElement = 1, // LayoutElement
		k_GraphicDescription = 2, // GraphicDescription
		k_BillOfMaterials = 3, // BillOfMaterials
		k_LimitedUniqueEntity = 4, // LimitedUniqueEntity
		k_IdentifiableEntity = 5, // IdentifiableEntity
		k_UniqueEntity = 6, // UniqueEntity
		k_ColorHighlight = 7, // ColorHighlight
		k_ShapeLabelDefiniton = 8, // ShapeLabelDefiniton
		k_Event = 9, // Event
		k_ReferenceMaterial = 10, // ReferenceMaterial
		k_CostAllocationData = 11, // CostAllocationData
		k_DistributionDefinition = 12, // DistributionDefinition
		k_SetupChangeoverDefinition = 13, // SetupChangeoverDefinition
		k_SetupDefinition = 14, // SetupDefinition
		k_SkillDefinition = 15, // SkillDefinition
		k_SkillLevel = 16, // SkillLevel
		k_Connection = 17, // Connection
		k_ResourceClass = 18, // ResourceClass
		k_MaintenancePlan = 19, // MaintenancePlan
		k_Resource = 20, // Resource
		k_MaintenanceProcess = 21, // MaintenanceProcess
		k_Process = 22, // Process
		k_Holiday = 23, // Holiday
		k_ProcessPlan = 24, // ProcessPlan
		k_Shift = 25, // Shift
		k_ShiftSchedule = 26, // ShiftSchedule
		k_Calendar = 27, // Calendar
		k_ScheduleItemEffortDescripton = 28, // ScheduleItemEffortDescripton
		k_Schedule = 29, // Schedule
		k_ScheduleItem = 30, // ScheduleItem
		k_Job = 31, // Job
		k_JobEffortDescription = 32, // JobEffortDescription
		k_Order = 33, // Order
		k_OrderLine = 34, // OrderLine
		k_InventoryItem = 35, // InventoryItem
		k_InventoryItemClass = 36, // InventoryItemClass
		k_CurvedSegment = 37, // CurvedSegment
		k_PartType = 38, // PartType
		k_ImageGraphic = 39, // ImageGraphic
		k_Part = 40, // Part
		k_SegmentShape = 41, // SegmentShape
		k_StraightSegment = 42, // StraightSegment
		k_ModelGraphic = 43, // ModelGraphic
		k_TextualAnnotation = 44, // TextualAnnotation
		k_LayoutObject = 45, // LayoutObject
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

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPropertyExtensibleEntity
