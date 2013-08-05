#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CImageResolution
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CImageResolution

#include "type_.CNotifyPropertyChangeBase.h"


namespace CMSD
{

class CImageResolution : public ::CMSD::CNotifyPropertyChangeBase
{
public:
	CMSD_EXPORT CImageResolution(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CImageResolution(CImageResolution const& init);
	void operator=(CImageResolution const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CImageResolution); }
	MemberElement<CPixelsPerUnitType, _altova_mi_altova_CImageResolution_altova_PixelsPerUnit> PixelsPerUnit;
	struct PixelsPerUnit { typedef Iterator<CPixelsPerUnitType> iterator; };
	MemberElement<CLayoutLengthUnitType, _altova_mi_altova_CImageResolution_altova_ScreenUnit> ScreenUnit;
	struct ScreenUnit { typedef Iterator<CLayoutLengthUnitType> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CImageResolution
