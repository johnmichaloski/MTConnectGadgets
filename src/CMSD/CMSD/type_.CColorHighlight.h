#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CColorHighlight
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CColorHighlight

#include "type_.CNotifyPropertyChangeBase.h"


namespace CMSD
{

class CColorHighlight : public ::CMSD::CNotifyPropertyChangeBase
{
public:
	CMSD_EXPORT CColorHighlight(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CColorHighlight(CColorHighlight const& init);
	void operator=(CColorHighlight const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CColorHighlight); }
	MemberElement<xs::CstringType, _altova_mi_altova_CColorHighlight_altova_LineColor> LineColor;
	struct LineColor { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CColorHighlight_altova_FillColor> FillColor;
	struct FillColor { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<CAlphaValueType, _altova_mi_altova_CColorHighlight_altova_AlphaValue> AlphaValue;
	struct AlphaValue { typedef Iterator<CAlphaValueType> iterator; };
	MemberElement<CProperty, _altova_mi_altova_CColorHighlight_altova_Property> Property;
	struct Property { typedef Iterator<CProperty> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CColorHighlight
