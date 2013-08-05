#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPlacement
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPlacement

#include "type_.CLayoutElementReference.h"


namespace CMSD
{

class CPlacement : public ::CMSD::CLayoutElementReference
{
public:
	CMSD_EXPORT CPlacement(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CPlacement(CPlacement const& init);
	void operator=(CPlacement const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CPlacement); }
	MemberElement<CCoordinate3D, _altova_mi_altova_CPlacement_altova_Location> Location;
	struct Location { typedef Iterator<CCoordinate3D> iterator; };
	MemberElement<CArrayOfChoice1, _altova_mi_altova_CPlacement_altova_Transformations> Transformations;
	struct Transformations { typedef Iterator<CArrayOfChoice1> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPlacement
