#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CTemperatureUnitType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CTemperatureUnitType



namespace CMSD
{

class CTemperatureUnitType : public TypeBase
{
public:
	CMSD_EXPORT CTemperatureUnitType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CTemperatureUnitType(CTemperatureUnitType const& init);
	void operator=(CTemperatureUnitType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CTemperatureUnitType); }

	enum EnumValues {
		Invalid = -1,
		k_Celsius = 0, // Celsius
		k_Fahrenheit = 1, // Fahrenheit
		k_kelvin = 2, // kelvin
		EnumValueCount
	};

	
	CMSD_EXPORT int GetEnumerationValue();
	CMSD_EXPORT void SetEnumerationValue( const int index);
	CMSD_EXPORT void operator=(const string_type& value);
	CMSD_EXPORT operator string_type();
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CTemperatureUnitType
