#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CAbstractEntityReference
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CAbstractEntityReference

#include "type_.CReferencingEntity.h"


namespace CMSD
{

class CAbstractEntityReference : public ::CMSD::CReferencingEntity
{
public:
	CMSD_EXPORT CAbstractEntityReference(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CAbstractEntityReference(CAbstractEntityReference const& init);
	void operator=(CAbstractEntityReference const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CAbstractEntityReference); }
	MemberElement<xs::CstringType, _altova_mi_altova_CAbstractEntityReference_altova_DocumentIdentifier> DocumentIdentifier;
	struct DocumentIdentifier { typedef Iterator<xs::CstringType> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CAbstractEntityReference
