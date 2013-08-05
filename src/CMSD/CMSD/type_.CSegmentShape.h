#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CSegmentShape
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CSegmentShape

#include "type_.CNotifyPropertyChangeBase.h"


namespace CMSD
{

class CSegmentShape : public ::CMSD::CNotifyPropertyChangeBase
{
public:
	CMSD_EXPORT CSegmentShape(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CSegmentShape(CSegmentShape const& init);
	void operator=(CSegmentShape const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CSegmentShape); }
	MemberElement<CSegmentTypeType, _altova_mi_altova_CSegmentShape_altova_Type> Type;
	struct Type { typedef Iterator<CSegmentTypeType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CSegmentShape_altova_SegmentNumber> SegmentNumber;
	struct SegmentNumber { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CSegmentShape_altova_Description> Description;
	struct Description { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<CBaseLocationType, _altova_mi_altova_CSegmentShape_altova_Base> Base;
	struct Base { typedef Iterator<CBaseLocationType> iterator; };
	MemberElement<CCoordinate2D, _altova_mi_altova_CSegmentShape_altova_Start> Start;
	struct Start { typedef Iterator<CCoordinate2D> iterator; };
	MemberElement<CWidthType4, _altova_mi_altova_CSegmentShape_altova_Width> Width;
	struct Width { typedef Iterator<CWidthType4> iterator; };
	MemberElement<CStartHeightType, _altova_mi_altova_CSegmentShape_altova_StartHeight> StartHeight;
	struct StartHeight { typedef Iterator<CStartHeightType> iterator; };
	MemberElement<CEndHeightType, _altova_mi_altova_CSegmentShape_altova_EndHeight> EndHeight;
	struct EndHeight { typedef Iterator<CEndHeightType> iterator; };
	MemberElement<CTrackWidthType, _altova_mi_altova_CSegmentShape_altova_TrackWidth> TrackWidth;
	struct TrackWidth { typedef Iterator<CTrackWidthType> iterator; };
	MemberElement<CColorHighlight, _altova_mi_altova_CSegmentShape_altova_Color> Color;
	struct Color { typedef Iterator<CColorHighlight> iterator; };
	MemberElement<CCoordinate2D, _altova_mi_altova_CSegmentShape_altova_End> End;
	struct End { typedef Iterator<CCoordinate2D> iterator; };
	MemberElement<CCoordinate2D, _altova_mi_altova_CSegmentShape_altova_RotationPoint> RotationPoint;
	struct RotationPoint { typedef Iterator<CCoordinate2D> iterator; };
	MemberElement<CRotationAngleType, _altova_mi_altova_CSegmentShape_altova_RotationAngle> RotationAngle;
	struct RotationAngle { typedef Iterator<CRotationAngleType> iterator; };
	MemberElement<CReferenceMaterialReference, _altova_mi_altova_CSegmentShape_altova_ReferenceMaterial> ReferenceMaterial;
	struct ReferenceMaterial { typedef Iterator<CReferenceMaterialReference> iterator; };
	MemberElement<CProperty, _altova_mi_altova_CSegmentShape_altova_Property> Property;
	struct Property { typedef Iterator<CProperty> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CSegmentShape
