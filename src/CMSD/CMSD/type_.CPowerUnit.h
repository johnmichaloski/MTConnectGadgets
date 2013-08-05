#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPowerUnit
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPowerUnit



namespace CMSD
{

class CPowerUnit : public TypeBase
{
public:
	CMSD_EXPORT CPowerUnit(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CPowerUnit(CPowerUnit const& init);
	void operator=(CPowerUnit const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_altova_CPowerUnit); }

	enum EnumValues {
		Invalid = -1,
		k_horsepower = 0, // horsepower
		k_watt = 1, // watt
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

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPowerUnit
