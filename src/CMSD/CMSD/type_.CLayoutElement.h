#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CLayoutElement
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CLayoutElement

#include "type_.CUniqueEntity.h"


namespace CMSD
{

class CLayoutElement : public ::CMSD::CUniqueEntity
{
public:
	CMSD_EXPORT CLayoutElement(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CLayoutElement(CLayoutElement const& init);
	void operator=(CLayoutElement const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CLayoutElement); }
	MemberElement<xs::CstringType, _altova_mi_altova_CLayoutElement_altova_Name> Name;
	struct Name { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<CResourceReference, _altova_mi_altova_CLayoutElement_altova_AssociatedResource> AssociatedResource;
	struct AssociatedResource { typedef Iterator<CResourceReference> iterator; };
	MemberElement<CBoundaryDefinition, _altova_mi_altova_CLayoutElement_altova_Boundary> Boundary;
	struct Boundary { typedef Iterator<CBoundaryDefinition> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CLayoutElement
