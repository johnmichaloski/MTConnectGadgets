#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPartReference
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPartReference

#include "type_.CAbstractEntityReference.h"


namespace CMSD
{

class CPartReference : public ::CMSD::CAbstractEntityReference
{
public:
	CMSD_EXPORT CPartReference(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CPartReference(CPartReference const& init);
	void operator=(CPartReference const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CPartReference); }
	MemberElement<xs::CstringType, _altova_mi_altova_CPartReference_altova_PartIdentifier> PartIdentifier;
	struct PartIdentifier { typedef Iterator<xs::CstringType> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPartReference
