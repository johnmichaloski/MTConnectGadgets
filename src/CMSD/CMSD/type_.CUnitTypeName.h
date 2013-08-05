#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CUnitTypeName
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CUnitTypeName



namespace CMSD
{

class CUnitTypeName : public TypeBase
{
public:
	CMSD_EXPORT CUnitTypeName(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CUnitTypeName(CUnitTypeName const& init);
	void operator=(CUnitTypeName const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_altova_CUnitTypeName); }

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
	void operator= (const string_type& value) 
	{
		altova::XmlFormatter* Formatter = static_cast<altova::XmlFormatter*>(altova::AnySimpleTypeFormatter);
		MsxmlTreeOperations::SetValue(GetNode(), Formatter->Format(value));
	}	
		
	operator string_type()
	{
		return CastAs<string_type >::Do(GetNode(), 0);
	}
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CUnitTypeName
