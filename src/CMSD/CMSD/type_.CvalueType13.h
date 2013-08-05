#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CvalueType13
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CvalueType13



namespace CMSD
{

class CvalueType13 : public TypeBase
{
public:
	CMSD_EXPORT CvalueType13(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CvalueType13(CvalueType13 const& init);
	void operator=(CvalueType13 const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_altova_CvalueType13); }

	enum EnumValues {
		Invalid = -1,
		k_preserve = 0, // preserve
		k_replace = 1, // replace
		k_collapse = 2, // collapse
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

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CvalueType13
