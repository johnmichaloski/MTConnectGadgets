#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CSpeedUnitType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CSpeedUnitType



namespace CMSD
{

class CSpeedUnitType : public TypeBase
{
public:
	CMSD_EXPORT CSpeedUnitType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CSpeedUnitType(CSpeedUnitType const& init);
	void operator=(CSpeedUnitType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CSpeedUnitType); }

	enum EnumValues {
		Invalid = -1,
		k_footPerSecond = 0, // footPerSecond
		k_kilometerPerHour = 1, // kilometerPerHour
		k_meterPerSecond = 2, // meterPerSecond
		k_milePerHour = 3, // milePerHour
		EnumValueCount
	};

	
	CMSD_EXPORT int GetEnumerationValue();
	CMSD_EXPORT void SetEnumerationValue( const int index);
	CMSD_EXPORT void operator=(const string_type& value);
	CMSD_EXPORT operator string_type();
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CSpeedUnitType
