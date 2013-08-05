#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CInventoryItemClassReference
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CInventoryItemClassReference

#include "type_.CAbstractEntityReference.h"


namespace CMSD
{

class CInventoryItemClassReference : public ::CMSD::CAbstractEntityReference
{
public:
	CMSD_EXPORT CInventoryItemClassReference(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CInventoryItemClassReference(CInventoryItemClassReference const& init);
	void operator=(CInventoryItemClassReference const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CInventoryItemClassReference); }
	MemberElement<xs::CstringType, _altova_mi_altova_CInventoryItemClassReference_altova_InventoryItemClassIdentifier> InventoryItemClassIdentifier;
	struct InventoryItemClassIdentifier { typedef Iterator<xs::CstringType> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CInventoryItemClassReference
