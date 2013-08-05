#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCoordinate2D
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCoordinate2D

#include "type_.CNotifyPropertyChangeBase.h"


namespace CMSD
{

class CCoordinate2D : public ::CMSD::CNotifyPropertyChangeBase
{
public:
	CMSD_EXPORT CCoordinate2D(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CCoordinate2D(CCoordinate2D const& init);
	void operator=(CCoordinate2D const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CCoordinate2D); }
	MemberElement<CXType, _altova_mi_altova_CCoordinate2D_altova_X> X;
	struct X { typedef Iterator<CXType> iterator; };
	MemberElement<CYType, _altova_mi_altova_CCoordinate2D_altova_Y> Y;
	struct Y { typedef Iterator<CYType> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCoordinate2D
