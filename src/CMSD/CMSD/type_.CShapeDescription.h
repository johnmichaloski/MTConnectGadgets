#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CShapeDescription
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CShapeDescription

#include "type_.CNotifyPropertyChangeBase.h"


namespace CMSD
{

class CShapeDescription : public ::CMSD::CNotifyPropertyChangeBase
{
public:
	CMSD_EXPORT CShapeDescription(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CShapeDescription(CShapeDescription const& init);
	void operator=(CShapeDescription const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CShapeDescription); }
	MemberElement<CShapeDescriptionTypeType, _altova_mi_altova_CShapeDescription_altova_ShapeType> ShapeType;
	struct ShapeType { typedef Iterator<CShapeDescriptionTypeType> iterator; };
	MemberElement<CBasicShape, _altova_mi_altova_CShapeDescription_altova_BasicShape> BasicShape;
	struct BasicShape { typedef Iterator<CBasicShape> iterator; };
	MemberElement<CGraphicDescription, _altova_mi_altova_CShapeDescription_altova_Graphic> Graphic;
	struct Graphic { typedef Iterator<CGraphicDescription> iterator; };
	MemberElement<CSegmentShape, _altova_mi_altova_CShapeDescription_altova_Segment> Segment;
	struct Segment { typedef Iterator<CSegmentShape> iterator; };
	MemberElement<CTextualAnnotation, _altova_mi_altova_CShapeDescription_altova_TextualAnnotation> TextualAnnotation;
	struct TextualAnnotation { typedef Iterator<CTextualAnnotation> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CShapeDescription
