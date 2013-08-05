#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CWeightType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CWeightType

#include "type_.CNotifyPropertyChangeBase.h"


namespace CMSD
{

class CWeightType : public ::CMSD::CNotifyPropertyChangeBase
{
public:
	CMSD_EXPORT CWeightType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CWeightType(CWeightType const& init);
	void operator=(CWeightType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CWeightType); }
	MemberElement<CWeightUnitType, _altova_mi_altova_CWeightType_altova_Unit> Unit;
	struct Unit { typedef Iterator<CWeightUnitType> iterator; };
	MemberElement<CValueType12, _altova_mi_altova_CWeightType_altova_Value2> Value2;
	struct Value2 { typedef Iterator<CValueType12> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CWeightType
