#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CBillOfMaterialsComponentReference
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CBillOfMaterialsComponentReference

#include "type_.CAbstractEntityReference.h"


namespace CMSD
{

class CBillOfMaterialsComponentReference : public ::CMSD::CAbstractEntityReference
{
public:
	CMSD_EXPORT CBillOfMaterialsComponentReference(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CBillOfMaterialsComponentReference(CBillOfMaterialsComponentReference const& init);
	void operator=(CBillOfMaterialsComponentReference const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CBillOfMaterialsComponentReference); }
	MemberElement<xs::CstringType, _altova_mi_altova_CBillOfMaterialsComponentReference_altova_BillOfMaterialsIdentifier> BillOfMaterialsIdentifier;
	struct BillOfMaterialsIdentifier { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CBillOfMaterialsComponentReference_altova_BillOfMaterialsComponentIdentifier> BillOfMaterialsComponentIdentifier;
	struct BillOfMaterialsComponentIdentifier { typedef Iterator<xs::CstringType> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CBillOfMaterialsComponentReference
