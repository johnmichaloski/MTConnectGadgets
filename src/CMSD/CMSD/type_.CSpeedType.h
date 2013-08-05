#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CSpeedType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CSpeedType

#include "type_.CNotifyPropertyChangeBase.h"


namespace CMSD
{

class CSpeedType : public ::CMSD::CNotifyPropertyChangeBase
{
public:
	CMSD_EXPORT CSpeedType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CSpeedType(CSpeedType const& init);
	void operator=(CSpeedType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CSpeedType); }
	MemberElement<CSpeedUnitType, _altova_mi_altova_CSpeedType_altova_Unit> Unit;
	struct Unit { typedef Iterator<CSpeedUnitType> iterator; };
	MemberElement<CValueType9, _altova_mi_altova_CSpeedType_altova_Value2> Value2;
	struct Value2 { typedef Iterator<CValueType9> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CSpeedType
