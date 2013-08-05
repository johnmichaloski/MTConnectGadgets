#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CUnitTypeNameType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CUnitTypeNameType



namespace CMSD
{

class CUnitTypeNameType : public TypeBase
{
public:
	CMSD_EXPORT CUnitTypeNameType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CUnitTypeNameType(CUnitTypeNameType const& init);
	void operator=(CUnitTypeNameType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CUnitTypeNameType); }

	enum EnumValues {
		Invalid = -1,
		k_AreaUnit = 0, // AreaUnit
		k_CurrencyUnit = 1, // CurrencyUnit
		k_LengthUnit = 2, // LengthUnit
		k_PowerUnit = 3, // PowerUnit
		k_SpeedUnit = 4, // SpeedUnit
		k_TemperatureUnit = 5, // TemperatureUnit
		k_WeightUnit = 6, // WeightUnit
		k_TimeUnit = 7, // TimeUnit
		k_VolumeUnit = 8, // VolumeUnit
		EnumValueCount
	};

	
	CMSD_EXPORT int GetEnumerationValue();
	CMSD_EXPORT void SetEnumerationValue( const int index);
	CMSD_EXPORT void operator=(const string_type& value);
	CMSD_EXPORT operator string_type();
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CUnitTypeNameType
