#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CSimpleDataTypeName
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CSimpleDataTypeName



namespace CMSD
{

class CSimpleDataTypeName : public TypeBase
{
public:
	CMSD_EXPORT CSimpleDataTypeName(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CSimpleDataTypeName(CSimpleDataTypeName const& init);
	void operator=(CSimpleDataTypeName const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_altova_CSimpleDataTypeName); }

	enum EnumValues {
		Invalid = -1,
		k_Time = 0, // Time
		k_Date = 1, // Date
		k_Timestamp = 2, // Timestamp
		k_String = 3, // String
		k_Identifier = 4, // Identifier
		k_URI = 5, // URI
		k_Decimal = 6, // Decimal
		k_Boolean = 7, // Boolean
		k_Integer = 8, // Integer
		k_NonNegativeInteger = 9, // NonNegativeInteger
		k_AreaUnit = 10, // AreaUnit
		k_CurrencyUnit = 11, // CurrencyUnit
		k_LengthUnit = 12, // LengthUnit
		k_PowerUnit = 13, // PowerUnit
		k_SpeedUnit = 14, // SpeedUnit
		k_TemperatureUnit = 15, // TemperatureUnit
		k_WeightUnit = 16, // WeightUnit
		k_TimeUnit = 17, // TimeUnit
		k_VolumeUnit = 18, // VolumeUnit
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

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CSimpleDataTypeName
