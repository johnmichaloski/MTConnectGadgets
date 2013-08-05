#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CShapeLabelDefinition
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CShapeLabelDefinition

#include "type_.CNotifyPropertyChangeBase.h"


namespace CMSD
{

class CShapeLabelDefinition : public ::CMSD::CNotifyPropertyChangeBase
{
public:
	CMSD_EXPORT CShapeLabelDefinition(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CShapeLabelDefinition(CShapeLabelDefinition const& init);
	void operator=(CShapeLabelDefinition const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CShapeLabelDefinition); }
	MemberElement<xs::CstringType, _altova_mi_altova_CShapeLabelDefinition_altova_Text> Text;
	struct Text { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CShapeLabelDefinition_altova_Color> Color;
	struct Color { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<CProperty, _altova_mi_altova_CShapeLabelDefinition_altova_Property> Property;
	struct Property { typedef Iterator<CProperty> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CShapeLabelDefinition
