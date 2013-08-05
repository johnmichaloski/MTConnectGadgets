#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPart
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPart

#include "type_.CUniqueEntity.h"


namespace CMSD
{

class CPart : public ::CMSD::CUniqueEntity
{
public:
	CMSD_EXPORT CPart(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CPart(CPart const& init);
	void operator=(CPart const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CPart); }
	MemberElement<CPartTypeReference, _altova_mi_altova_CPart_altova_PartType> PartType;
	struct PartType { typedef Iterator<CPartTypeReference> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CPart_altova_Name> Name;
	struct Name { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<CPartProductionStatusType, _altova_mi_altova_CPart_altova_ProductionStatus> ProductionStatus;
	struct ProductionStatus { typedef Iterator<CPartProductionStatusType> iterator; };
	MemberElement<CLocationDefinition, _altova_mi_altova_CPart_altova_Location> Location;
	struct Location { typedef Iterator<CLocationDefinition> iterator; };
	MemberElement<CBillOfMaterialsReference, _altova_mi_altova_CPart_altova_BillOfMaterials> BillOfMaterials;
	struct BillOfMaterials { typedef Iterator<CBillOfMaterialsReference> iterator; };
	MemberElement<CProcessPlanReference, _altova_mi_altova_CPart_altova_ProcessPlan> ProcessPlan;
	struct ProcessPlan { typedef Iterator<CProcessPlanReference> iterator; };
	MemberElement<CProcessReference, _altova_mi_altova_CPart_altova_LastFinishedProcessStep> LastFinishedProcessStep;
	struct LastFinishedProcessStep { typedef Iterator<CProcessReference> iterator; };
	MemberElement<CGrossDimensions, _altova_mi_altova_CPart_altova_Size> Size;
	struct Size { typedef Iterator<CGrossDimensions> iterator; };
	MemberElement<CWeightType, _altova_mi_altova_CPart_altova_Weight> Weight;
	struct Weight { typedef Iterator<CWeightType> iterator; };
	MemberElement<CLotInformation, _altova_mi_altova_CPart_altova_Lot> Lot;
	struct Lot { typedef Iterator<CLotInformation> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPart
