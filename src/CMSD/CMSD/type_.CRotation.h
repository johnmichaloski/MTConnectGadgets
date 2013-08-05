#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CRotation
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CRotation

#include "type_.CTransformationOperation.h"


namespace CMSD
{

class CRotation : public ::CMSD::CTransformationOperation
{
public:
	CMSD_EXPORT CRotation(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CRotation(CRotation const& init);
	void operator=(CRotation const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CRotation); }
	MemberElement<CXDegreeType, _altova_mi_altova_CRotation_altova_XDegree> XDegree;
	struct XDegree { typedef Iterator<CXDegreeType> iterator; };
	MemberElement<CYDegreeType, _altova_mi_altova_CRotation_altova_YDegree> YDegree;
	struct YDegree { typedef Iterator<CYDegreeType> iterator; };
	MemberElement<CZDegreeType, _altova_mi_altova_CRotation_altova_ZDegree> ZDegree;
	struct ZDegree { typedef Iterator<CZDegreeType> iterator; };
	MemberElement<CCoordinate3D, _altova_mi_altova_CRotation_altova_Origin> Origin;
	struct Origin { typedef Iterator<CCoordinate3D> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CRotation
