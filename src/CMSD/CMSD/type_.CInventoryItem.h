#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CInventoryItem
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CInventoryItem

#include "type_.CUniqueEntity.h"


namespace CMSD
{

class CInventoryItem : public ::CMSD::CUniqueEntity
{
public:
	CMSD_EXPORT CInventoryItem(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CInventoryItem(CInventoryItem const& init);
	void operator=(CInventoryItem const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CInventoryItem); }
	MemberElement<xs::CstringType, _altova_mi_altova_CInventoryItem_altova_Name> Name;
	struct Name { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<CInventoryItemClassReference, _altova_mi_altova_CInventoryItem_altova_InventoryItemClass> InventoryItemClass;
	struct InventoryItemClass { typedef Iterator<CInventoryItemClassReference> iterator; };
	MemberElement<CQuantityOnHandType, _altova_mi_altova_CInventoryItem_altova_QuantityOnHand> QuantityOnHand;
	struct QuantityOnHand { typedef Iterator<CQuantityOnHandType> iterator; };
	MemberElement<CLocationDefinition, _altova_mi_altova_CInventoryItem_altova_Location> Location;
	struct Location { typedef Iterator<CLocationDefinition> iterator; };
	MemberElement<CPartReference, _altova_mi_altova_CInventoryItem_altova_AssociatedPart> AssociatedPart;
	struct AssociatedPart { typedef Iterator<CPartReference> iterator; };
	MemberElement<CResourceReference, _altova_mi_altova_CInventoryItem_altova_AssociatedResource> AssociatedResource;
	struct AssociatedResource { typedef Iterator<CResourceReference> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CInventoryItem
