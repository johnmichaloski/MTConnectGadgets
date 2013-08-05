#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CGrossDimensions
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CGrossDimensions

#include "type_.CNotifyPropertyChangeBase.h"


namespace CMSD
{

class CGrossDimensions : public ::CMSD::CNotifyPropertyChangeBase
{
public:
	CMSD_EXPORT CGrossDimensions(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CGrossDimensions(CGrossDimensions const& init);
	void operator=(CGrossDimensions const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CGrossDimensions); }
	MemberElement<CLengthUnitType, _altova_mi_altova_CGrossDimensions_altova_Unit> Unit;
	struct Unit { typedef Iterator<CLengthUnitType> iterator; };
	MemberElement<CWidthType3, _altova_mi_altova_CGrossDimensions_altova_Width> Width;
	struct Width { typedef Iterator<CWidthType3> iterator; };
	MemberElement<CDepthType3, _altova_mi_altova_CGrossDimensions_altova_Depth> Depth;
	struct Depth { typedef Iterator<CDepthType3> iterator; };
	MemberElement<CHeightType3, _altova_mi_altova_CGrossDimensions_altova_Height> Height;
	struct Height { typedef Iterator<CHeightType3> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CGrossDimensions
