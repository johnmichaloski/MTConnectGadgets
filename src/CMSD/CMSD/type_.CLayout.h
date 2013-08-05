#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CLayout
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CLayout

#include "type_.CLayoutElement.h"


namespace CMSD
{

class CLayout : public ::CMSD::CLayoutElement
{
public:
	CMSD_EXPORT CLayout(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CLayout(CLayout const& init);
	void operator=(CLayout const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CLayout); }
	MemberElement<CPlacement, _altova_mi_altova_CLayout_altova_Placement> Placement;
	struct Placement { typedef Iterator<CPlacement> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CLayout
