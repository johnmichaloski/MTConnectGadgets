#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CDayType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CDayType



namespace CMSD
{

class CDayType : public TypeBase
{
public:
	CMSD_EXPORT CDayType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CDayType(CDayType const& init);
	void operator=(CDayType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CDayType); }

	enum EnumValues {
		Invalid = -1,
		k_sunday = 0, // sunday
		k_monday = 1, // monday
		k_tuesday = 2, // tuesday
		k_wednesday = 3, // wednesday
		k_thursday = 4, // thursday
		k_friday = 5, // friday
		k_saturday = 6, // saturday
		EnumValueCount
	};

	
	CMSD_EXPORT int GetEnumerationValue();
	CMSD_EXPORT void SetEnumerationValue( const int index);
	CMSD_EXPORT void operator=(const string_type& value);
	CMSD_EXPORT operator string_type();
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CDayType
