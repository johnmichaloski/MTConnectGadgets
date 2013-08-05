#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CReferenceMaterialReference
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CReferenceMaterialReference

#include "type_.CAbstractEntityReference.h"


namespace CMSD
{

class CReferenceMaterialReference : public ::CMSD::CAbstractEntityReference
{
public:
	CMSD_EXPORT CReferenceMaterialReference(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CReferenceMaterialReference(CReferenceMaterialReference const& init);
	void operator=(CReferenceMaterialReference const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CReferenceMaterialReference); }
	MemberElement<xs::CstringType, _altova_mi_altova_CReferenceMaterialReference_altova_ReferenceMaterialIdentifier> ReferenceMaterialIdentifier;
	struct ReferenceMaterialIdentifier { typedef Iterator<xs::CstringType> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CReferenceMaterialReference
