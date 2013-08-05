#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CConnectionType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CConnectionType



namespace CMSD
{

class CConnectionType : public TypeBase
{
public:
	CMSD_EXPORT CConnectionType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CConnectionType(CConnectionType const& init);
	void operator=(CConnectionType const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_altova_CConnectionType); }

	enum EnumValues {
		Invalid = -1,
		k_input = 0, // input
		k_output = 1, // output
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

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CConnectionType
