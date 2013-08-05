#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CBasicShape
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CBasicShape

#include "type_.CNotifyPropertyChangeBase.h"


namespace CMSD
{

class CBasicShape : public ::CMSD::CNotifyPropertyChangeBase
{
public:
	CMSD_EXPORT CBasicShape(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CBasicShape(CBasicShape const& init);
	void operator=(CBasicShape const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CBasicShape); }
	MemberElement<CBasicShapeTypeType, _altova_mi_altova_CBasicShape_altova_Type> Type;
	struct Type { typedef Iterator<CBasicShapeTypeType> iterator; };
	MemberElement<CHeightType, _altova_mi_altova_CBasicShape_altova_Height> Height;
	struct Height { typedef Iterator<CHeightType> iterator; };
	MemberElement<CColorHighlight, _altova_mi_altova_CBasicShape_altova_Color> Color;
	struct Color { typedef Iterator<CColorHighlight> iterator; };
	MemberElement<CShapeLabelDefinition, _altova_mi_altova_CBasicShape_altova_Label> Label;
	struct Label { typedef Iterator<CShapeLabelDefinition> iterator; };
	MemberElement<CWidthType, _altova_mi_altova_CBasicShape_altova_Width> Width;
	struct Width { typedef Iterator<CWidthType> iterator; };
	MemberElement<CDepthType, _altova_mi_altova_CBasicShape_altova_Depth> Depth;
	struct Depth { typedef Iterator<CDepthType> iterator; };
	MemberElement<CRadiusType, _altova_mi_altova_CBasicShape_altova_Radius> Radius;
	struct Radius { typedef Iterator<CRadiusType> iterator; };
	MemberElement<CAngleType, _altova_mi_altova_CBasicShape_altova_Angle> Angle;
	struct Angle { typedef Iterator<CAngleType> iterator; };
	MemberElement<CCoordinate2D, _altova_mi_altova_CBasicShape_altova_Center> Center;
	struct Center { typedef Iterator<CCoordinate2D> iterator; };
	MemberElement<CCoordinate2D, _altova_mi_altova_CBasicShape_altova_Point> Point;
	struct Point { typedef Iterator<CCoordinate2D> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CBasicShape
