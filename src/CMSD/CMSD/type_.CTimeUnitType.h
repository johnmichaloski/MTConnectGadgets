#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CTimeUnitType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CTimeUnitType



namespace CMSD
{

class CTimeUnitType : public TypeBase
{
public:
	CMSD_EXPORT CTimeUnitType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CTimeUnitType(CTimeUnitType const& init);
	void operator=(CTimeUnitType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CTimeUnitType); }

	enum EnumValues {
		Invalid = -1,
		k_second = 0, // second
		k_minute = 1, // minute
		k_hour = 2, // hour
		k_day = 3, // day
		k_month = 4, // month
		k_week = 5, // week
		k_year = 6, // year
		EnumValueCount
	};

	
	CMSD_EXPORT int GetEnumerationValue();
	CMSD_EXPORT void SetEnumerationValue( const int index);
	CMSD_EXPORT void operator=(const string_type& value);
	CMSD_EXPORT operator string_type();
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CTimeUnitType
