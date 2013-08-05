#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPowerUnitType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPowerUnitType



namespace CMSD
{

class CPowerUnitType : public TypeBase
{
public:
	CMSD_EXPORT CPowerUnitType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CPowerUnitType(CPowerUnitType const& init);
	void operator=(CPowerUnitType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CPowerUnitType); }

	enum EnumValues {
		Invalid = -1,
		k_horsepower = 0, // horsepower
		k_watt = 1, // watt
		EnumValueCount
	};

	
	CMSD_EXPORT int GetEnumerationValue();
	CMSD_EXPORT void SetEnumerationValue( const int index);
	CMSD_EXPORT void operator=(const string_type& value);
	CMSD_EXPORT operator string_type();
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPowerUnitType
