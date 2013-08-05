#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPartTypeReference
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPartTypeReference

#include "type_.CAbstractEntityReference.h"


namespace CMSD
{

class CPartTypeReference : public ::CMSD::CAbstractEntityReference
{
public:
	CMSD_EXPORT CPartTypeReference(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CPartTypeReference(CPartTypeReference const& init);
	void operator=(CPartTypeReference const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CPartTypeReference); }
	MemberElement<xs::CstringType, _altova_mi_altova_CPartTypeReference_altova_PartTypeIdentifier> PartTypeIdentifier;
	struct PartTypeIdentifier { typedef Iterator<xs::CstringType> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPartTypeReference
