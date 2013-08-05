#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CGraphicDescription
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CGraphicDescription

#include "type_.CNotifyPropertyChangeBase.h"


namespace CMSD
{

class CGraphicDescription : public ::CMSD::CNotifyPropertyChangeBase
{
public:
	CMSD_EXPORT CGraphicDescription(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CGraphicDescription(CGraphicDescription const& init);
	void operator=(CGraphicDescription const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CGraphicDescription); }
	MemberElement<CGraphicDescriptionTypeType, _altova_mi_altova_CGraphicDescription_altova_GraphicType> GraphicType;
	struct GraphicType { typedef Iterator<CGraphicDescriptionTypeType> iterator; };
	MemberElement<CFileNameType, _altova_mi_altova_CGraphicDescription_altova_FileName> FileName;
	struct FileName { typedef Iterator<CFileNameType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CGraphicDescription_altova_FileType> FileType;
	struct FileType { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<CArrayOfChoice2, _altova_mi_altova_CGraphicDescription_altova_Transformations> Transformations;
	struct Transformations { typedef Iterator<CArrayOfChoice2> iterator; };
	MemberElement<CProperty, _altova_mi_altova_CGraphicDescription_altova_Property> Property;
	struct Property { typedef Iterator<CProperty> iterator; };
	MemberElement<CImageResolution, _altova_mi_altova_CGraphicDescription_altova_ImageResolution> ImageResolution;
	struct ImageResolution { typedef Iterator<CImageResolution> iterator; };
	MemberElement<CSpatialDimension, _altova_mi_altova_CGraphicDescription_altova_ImageDimension> ImageDimension;
	struct ImageDimension { typedef Iterator<CSpatialDimension> iterator; };
	MemberElement<CLayoutLengthUnitType, _altova_mi_altova_CGraphicDescription_altova_ModelUnit> ModelUnit;
	struct ModelUnit { typedef Iterator<CLayoutLengthUnitType> iterator; };
	MemberElement<CSpatialDimension, _altova_mi_altova_CGraphicDescription_altova_ModelDimension> ModelDimension;
	struct ModelDimension { typedef Iterator<CSpatialDimension> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CGraphicDescription
