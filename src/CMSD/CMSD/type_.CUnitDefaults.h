#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CUnitDefaults
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CUnitDefaults

#include "type_.CNotifyPropertyChangeBase.h"


namespace CMSD
{

class CUnitDefaults : public ::CMSD::CNotifyPropertyChangeBase
{
public:
	CMSD_EXPORT CUnitDefaults(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CUnitDefaults(CUnitDefaults const& init);
	void operator=(CUnitDefaults const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CUnitDefaults); }
	MemberElement<CAreaUnitType, _altova_mi_altova_CUnitDefaults_altova_AreaUnit> AreaUnit;
	struct AreaUnit { typedef Iterator<CAreaUnitType> iterator; };
	MemberElement<CLengthUnitType, _altova_mi_altova_CUnitDefaults_altova_LengthUnit> LengthUnit;
	struct LengthUnit { typedef Iterator<CLengthUnitType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CUnitDefaults_altova_CurrencyUnit> CurrencyUnit;
	struct CurrencyUnit { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<CPowerUnitType, _altova_mi_altova_CUnitDefaults_altova_PowerUnit> PowerUnit;
	struct PowerUnit { typedef Iterator<CPowerUnitType> iterator; };
	MemberElement<CSpeedUnitType, _altova_mi_altova_CUnitDefaults_altova_SpeedUnit> SpeedUnit;
	struct SpeedUnit { typedef Iterator<CSpeedUnitType> iterator; };
	MemberElement<CTemperatureUnitType, _altova_mi_altova_CUnitDefaults_altova_TemperatureUnit> TemperatureUnit;
	struct TemperatureUnit { typedef Iterator<CTemperatureUnitType> iterator; };
	MemberElement<CTimeUnitType, _altova_mi_altova_CUnitDefaults_altova_TimeUnit> TimeUnit;
	struct TimeUnit { typedef Iterator<CTimeUnitType> iterator; };
	MemberElement<CVolumeUnitType, _altova_mi_altova_CUnitDefaults_altova_VolumeUnit> VolumeUnit;
	struct VolumeUnit { typedef Iterator<CVolumeUnitType> iterator; };
	MemberElement<CWeightUnitType, _altova_mi_altova_CUnitDefaults_altova_WeightUnit> WeightUnit;
	struct WeightUnit { typedef Iterator<CWeightUnitType> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CUnitDefaults
