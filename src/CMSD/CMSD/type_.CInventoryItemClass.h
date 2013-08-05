#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CInventoryItemClass
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CInventoryItemClass

#include "type_.CUniqueEntity.h"


namespace CMSD
{

class CInventoryItemClass : public ::CMSD::CUniqueEntity
{
public:
	CMSD_EXPORT CInventoryItemClass(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CInventoryItemClass(CInventoryItemClass const& init);
	void operator=(CInventoryItemClass const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CInventoryItemClass); }
	MemberElement<xs::CstringType, _altova_mi_altova_CInventoryItemClass_altova_Name> Name;
	struct Name { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<CInventoryItemTypeType, _altova_mi_altova_CInventoryItemClass_altova_InventoryItemType> InventoryItemType;
	struct InventoryItemType { typedef Iterator<CInventoryItemTypeType> iterator; };
	MemberElement<CPartTypeReference, _altova_mi_altova_CInventoryItemClass_altova_PartType> PartType;
	struct PartType { typedef Iterator<CPartTypeReference> iterator; };
	MemberElement<CResourceClassReference, _altova_mi_altova_CInventoryItemClass_altova_ResourceClass> ResourceClass;
	struct ResourceClass { typedef Iterator<CResourceClassReference> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CInventoryItemClass
