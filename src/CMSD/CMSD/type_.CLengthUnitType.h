#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CLengthUnitType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CLengthUnitType



namespace CMSD
{

class CLengthUnitType : public TypeBase
{
public:
	CMSD_EXPORT CLengthUnitType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CLengthUnitType(CLengthUnitType const& init);
	void operator=(CLengthUnitType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CLengthUnitType); }

	enum EnumValues {
		Invalid = -1,
		k_millimeter = 0, // millimeter
		k_centimeter = 1, // centimeter
		k_meter = 2, // meter
		k_kilometer = 3, // kilometer
		k_inch = 4, // inch
		k_foot = 5, // foot
		k_yard = 6, // yard
		k_mile = 7, // mile
		EnumValueCount
	};

	
	CMSD_EXPORT int GetEnumerationValue();
	CMSD_EXPORT void SetEnumerationValue( const int index);
	CMSD_EXPORT void operator=(const string_type& value);
	CMSD_EXPORT operator string_type();
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CLengthUnitType
