#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CResourceClassReference
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CResourceClassReference

#include "type_.CAbstractEntityReference.h"


namespace CMSD
{

class CResourceClassReference : public ::CMSD::CAbstractEntityReference
{
public:
	CMSD_EXPORT CResourceClassReference(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CResourceClassReference(CResourceClassReference const& init);
	void operator=(CResourceClassReference const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CResourceClassReference); }
	MemberElement<xs::CstringType, _altova_mi_altova_CResourceClassReference_altova_ResourceClassIdentifier> ResourceClassIdentifier;
	struct ResourceClassIdentifier { typedef Iterator<xs::CstringType> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CResourceClassReference
