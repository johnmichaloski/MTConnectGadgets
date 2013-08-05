#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCoordinate3D
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCoordinate3D

#include "type_.CCoordinate2D.h"


namespace CMSD
{

class CCoordinate3D : public ::CMSD::CCoordinate2D
{
public:
	CMSD_EXPORT CCoordinate3D(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CCoordinate3D(CCoordinate3D const& init);
	void operator=(CCoordinate3D const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CCoordinate3D); }
	MemberElement<CZType, _altova_mi_altova_CCoordinate3D_altova_Z> Z;
	struct Z { typedef Iterator<CZType> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCoordinate3D
