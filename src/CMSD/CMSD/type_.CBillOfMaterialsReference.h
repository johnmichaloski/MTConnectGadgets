#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CBillOfMaterialsReference
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CBillOfMaterialsReference

#include "type_.CAbstractEntityReference.h"


namespace CMSD
{

class CBillOfMaterialsReference : public ::CMSD::CAbstractEntityReference
{
public:
	CMSD_EXPORT CBillOfMaterialsReference(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CBillOfMaterialsReference(CBillOfMaterialsReference const& init);
	void operator=(CBillOfMaterialsReference const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CBillOfMaterialsReference); }
	MemberElement<xs::CstringType, _altova_mi_altova_CBillOfMaterialsReference_altova_BillOfMaterialsIdentifier> BillOfMaterialsIdentifier;
	struct BillOfMaterialsIdentifier { typedef Iterator<xs::CstringType> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CBillOfMaterialsReference
