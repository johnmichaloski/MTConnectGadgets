#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CTextualAnnotation
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CTextualAnnotation

#include "type_.CNotifyPropertyChangeBase.h"


namespace CMSD
{

class CTextualAnnotation : public ::CMSD::CNotifyPropertyChangeBase
{
public:
	CMSD_EXPORT CTextualAnnotation(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CTextualAnnotation(CTextualAnnotation const& init);
	void operator=(CTextualAnnotation const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CTextualAnnotation); }
	MemberElement<CCoordinate3D, _altova_mi_altova_CTextualAnnotation_altova_AttachPoint> AttachPoint;
	struct AttachPoint { typedef Iterator<CCoordinate3D> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CTextualAnnotation_altova_Text> Text;
	struct Text { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<CTextAnchorLocationType, _altova_mi_altova_CTextualAnnotation_altova_TextAnchorLocation> TextAnchorLocation;
	struct TextAnchorLocation { typedef Iterator<CTextAnchorLocationType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CTextualAnnotation_altova_Color> Color;
	struct Color { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CTextualAnnotation_altova_Style> Style;
	struct Style { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<CTextAngleType, _altova_mi_altova_CTextualAnnotation_altova_TextAngle> TextAngle;
	struct TextAngle { typedef Iterator<CTextAngleType> iterator; };
	MemberElement<CProperty, _altova_mi_altova_CTextualAnnotation_altova_Property> Property;
	struct Property { typedef Iterator<CProperty> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CTextualAnnotation
