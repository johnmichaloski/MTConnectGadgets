#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CTemperatureType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CTemperatureType

#include "type_.CNotifyPropertyChangeBase.h"


namespace CMSD
{

class CTemperatureType : public ::CMSD::CNotifyPropertyChangeBase
{
public:
	CMSD_EXPORT CTemperatureType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CTemperatureType(CTemperatureType const& init);
	void operator=(CTemperatureType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CTemperatureType); }
	MemberElement<CTemperatureUnitType, _altova_mi_altova_CTemperatureType_altova_Unit> Unit;
	struct Unit { typedef Iterator<CTemperatureUnitType> iterator; };
	MemberElement<CValueType10, _altova_mi_altova_CTemperatureType_altova_Value2> Value2;
	struct Value2 { typedef Iterator<CValueType10> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CTemperatureType
