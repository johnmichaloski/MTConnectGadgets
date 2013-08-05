#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CBillOfMaterialsComponent
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CBillOfMaterialsComponent

#include "type_.CLimitedUniqueEntity.h"


namespace CMSD
{

class CBillOfMaterialsComponent : public ::CMSD::CLimitedUniqueEntity
{
public:
	CMSD_EXPORT CBillOfMaterialsComponent(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CBillOfMaterialsComponent(CBillOfMaterialsComponent const& init);
	void operator=(CBillOfMaterialsComponent const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CBillOfMaterialsComponent); }
	MemberElement<CQuantityType2, _altova_mi_altova_CBillOfMaterialsComponent_altova_Quantity> Quantity;
	struct Quantity { typedef Iterator<CQuantityType2> iterator; };
	MemberElement<CPartTypeReference, _altova_mi_altova_CBillOfMaterialsComponent_altova_PartType> PartType;
	struct PartType { typedef Iterator<CPartTypeReference> iterator; };
	MemberElement<CPartReference, _altova_mi_altova_CBillOfMaterialsComponent_altova_PartInstance> PartInstance;
	struct PartInstance { typedef Iterator<CPartReference> iterator; };
	MemberElement<CBillOfMaterialsComponentReference, _altova_mi_altova_CBillOfMaterialsComponent_altova_SubComponent> SubComponent;
	struct SubComponent { typedef Iterator<CBillOfMaterialsComponentReference> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CBillOfMaterialsComponent
