#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CTimeUnit
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CTimeUnit



namespace CMSD
{

class CTimeUnit : public TypeBase
{
public:
	CMSD_EXPORT CTimeUnit(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CTimeUnit(CTimeUnit const& init);
	void operator=(CTimeUnit const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_altova_CTimeUnit); }

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

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CTimeUnit
