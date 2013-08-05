#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CResourceReference
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CResourceReference

#include "type_.CAbstractEntityReference.h"


namespace CMSD
{

class CResourceReference : public ::CMSD::CAbstractEntityReference
{
public:
	CMSD_EXPORT CResourceReference(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CResourceReference(CResourceReference const& init);
	void operator=(CResourceReference const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CResourceReference); }
	MemberElement<xs::CstringType, _altova_mi_altova_CResourceReference_altova_ResourceIdentifier> ResourceIdentifier;
	struct ResourceIdentifier { typedef Iterator<xs::CstringType> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CResourceReference
