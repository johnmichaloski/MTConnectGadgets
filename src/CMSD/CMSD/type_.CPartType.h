#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPartType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPartType

#include "type_.CUniqueEntity.h"


namespace CMSD
{

class CPartType : public ::CMSD::CUniqueEntity
{
public:
	CMSD_EXPORT CPartType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CPartType(CPartType const& init);
	void operator=(CPartType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CPartType); }
	MemberElement<xs::CstringType, _altova_mi_altova_CPartType_altova_Name> Name;
	struct Name { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<CBillOfMaterialsReference, _altova_mi_altova_CPartType_altova_BillOfMaterials> BillOfMaterials;
	struct BillOfMaterials { typedef Iterator<CBillOfMaterialsReference> iterator; };
	MemberElement<CProcessPlanReference, _altova_mi_altova_CPartType_altova_ProcessPlan> ProcessPlan;
	struct ProcessPlan { typedef Iterator<CProcessPlanReference> iterator; };
	MemberElement<CGrossDimensions, _altova_mi_altova_CPartType_altova_Size> Size;
	struct Size { typedef Iterator<CGrossDimensions> iterator; };
	MemberElement<CWeightType, _altova_mi_altova_CPartType_altova_Weight> Weight;
	struct Weight { typedef Iterator<CWeightType> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPartType
