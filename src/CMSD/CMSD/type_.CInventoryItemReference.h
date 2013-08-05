#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CInventoryItemReference
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CInventoryItemReference

#include "type_.CAbstractEntityReference.h"


namespace CMSD
{

class CInventoryItemReference : public ::CMSD::CAbstractEntityReference
{
public:
	CMSD_EXPORT CInventoryItemReference(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CInventoryItemReference(CInventoryItemReference const& init);
	void operator=(CInventoryItemReference const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CInventoryItemReference); }
	MemberElement<xs::CstringType, _altova_mi_altova_CInventoryItemReference_altova_InventoryItemIdentifier> InventoryItemIdentifier;
	struct InventoryItemIdentifier { typedef Iterator<xs::CstringType> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CInventoryItemReference
