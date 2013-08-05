#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CBoundaryDefinition
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CBoundaryDefinition

#include "type_.CSpatialDimension.h"


namespace CMSD
{

class CBoundaryDefinition : public ::CMSD::CSpatialDimension
{
public:
	CMSD_EXPORT CBoundaryDefinition(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CBoundaryDefinition(CBoundaryDefinition const& init);
	void operator=(CBoundaryDefinition const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CBoundaryDefinition); }
	MemberElement<CLayoutLengthUnitType, _altova_mi_altova_CBoundaryDefinition_altova_Unit> Unit;
	struct Unit { typedef Iterator<CLayoutLengthUnitType> iterator; };
	MemberElement<CCoordinateSystemType, _altova_mi_altova_CBoundaryDefinition_altova_CoordinateSystem> CoordinateSystem;
	struct CoordinateSystem { typedef Iterator<CCoordinateSystemType> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CBoundaryDefinition
