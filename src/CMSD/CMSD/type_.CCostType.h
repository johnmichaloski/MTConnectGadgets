#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCostType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCostType



namespace CMSD
{

class CCostType : public TypeBase
{
public:
	CMSD_EXPORT CCostType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CCostType(CCostType const& init);
	void operator=(CCostType const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_altova_CCostType); }

	enum EnumValues {
		Invalid = -1,
		k_fixed = 0, // fixed
		k_variable = 1, // variable
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

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCostType
