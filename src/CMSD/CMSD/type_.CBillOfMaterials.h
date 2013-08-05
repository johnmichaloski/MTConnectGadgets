#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CBillOfMaterials
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CBillOfMaterials

#include "type_.CUniqueEntity.h"


namespace CMSD
{

class CBillOfMaterials : public ::CMSD::CUniqueEntity
{
public:
	CMSD_EXPORT CBillOfMaterials(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CBillOfMaterials(CBillOfMaterials const& init);
	void operator=(CBillOfMaterials const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CBillOfMaterials); }
	MemberElement<xs::CstringType, _altova_mi_altova_CBillOfMaterials_altova_Name> Name;
	struct Name { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<CPartTypeReference, _altova_mi_altova_CBillOfMaterials_altova_PartType> PartType;
	struct PartType { typedef Iterator<CPartTypeReference> iterator; };
	MemberElement<CPartReference, _altova_mi_altova_CBillOfMaterials_altova_PartInstance> PartInstance;
	struct PartInstance { typedef Iterator<CPartReference> iterator; };
	MemberElement<CBillOfMaterialsComponentReference, _altova_mi_altova_CBillOfMaterials_altova_MainComponent> MainComponent;
	struct MainComponent { typedef Iterator<CBillOfMaterialsComponentReference> iterator; };
	MemberElement<CBillOfMaterialsComponent, _altova_mi_altova_CBillOfMaterials_altova_BillOfMaterialsComponent> BillOfMaterialsComponent;
	struct BillOfMaterialsComponent { typedef Iterator<CBillOfMaterialsComponent> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CBillOfMaterials
