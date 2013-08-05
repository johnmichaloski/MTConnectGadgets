#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CDay
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CDay



namespace CMSD
{

class CDay : public TypeBase
{
public:
	CMSD_EXPORT CDay(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CDay(CDay const& init);
	void operator=(CDay const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_altova_CDay); }

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

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CDay
