#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CLayoutElementReference
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CLayoutElementReference

#include "type_.CAbstractEntityReference.h"


namespace CMSD
{

class CLayoutElementReference : public ::CMSD::CAbstractEntityReference
{
public:
	CMSD_EXPORT CLayoutElementReference(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CLayoutElementReference(CLayoutElementReference const& init);
	void operator=(CLayoutElementReference const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CLayoutElementReference); }
	MemberElement<xs::CstringType, _altova_mi_altova_CLayoutElementReference_altova_LayoutElementIdentifier> LayoutElementIdentifier;
	struct LayoutElementIdentifier { typedef Iterator<xs::CstringType> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CLayoutElementReference
