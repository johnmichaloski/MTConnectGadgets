#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CAreaType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CAreaType

#include "type_.CNotifyPropertyChangeBase.h"


namespace CMSD
{

class CAreaType : public ::CMSD::CNotifyPropertyChangeBase
{
public:
	CMSD_EXPORT CAreaType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CAreaType(CAreaType const& init);
	void operator=(CAreaType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CAreaType); }
	MemberElement<CAreaUnitType, _altova_mi_altova_CAreaType_altova_Unit> Unit;
	struct Unit { typedef Iterator<CAreaUnitType> iterator; };
	MemberElement<CValueType, _altova_mi_altova_CAreaType_altova_Value2> Value2;
	struct Value2 { typedef Iterator<CValueType> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CAreaType
