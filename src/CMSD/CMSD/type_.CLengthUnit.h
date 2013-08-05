#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CLengthUnit
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CLengthUnit



namespace CMSD
{

class CLengthUnit : public TypeBase
{
public:
	CMSD_EXPORT CLengthUnit(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CLengthUnit(CLengthUnit const& init);
	void operator=(CLengthUnit const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_altova_CLengthUnit); }

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

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CLengthUnit
