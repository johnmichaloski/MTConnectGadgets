#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CSpatialDimension
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CSpatialDimension

#include "type_.CNotifyPropertyChangeBase.h"


namespace CMSD
{

class CSpatialDimension : public ::CMSD::CNotifyPropertyChangeBase
{
public:
	CMSD_EXPORT CSpatialDimension(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CSpatialDimension(CSpatialDimension const& init);
	void operator=(CSpatialDimension const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CSpatialDimension); }
	MemberElement<CWidthType2, _altova_mi_altova_CSpatialDimension_altova_Width> Width;
	struct Width { typedef Iterator<CWidthType2> iterator; };
	MemberElement<CDepthType2, _altova_mi_altova_CSpatialDimension_altova_Depth> Depth;
	struct Depth { typedef Iterator<CDepthType2> iterator; };
	MemberElement<CHeightType2, _altova_mi_altova_CSpatialDimension_altova_Height> Height;
	struct Height { typedef Iterator<CHeightType2> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CSpatialDimension
