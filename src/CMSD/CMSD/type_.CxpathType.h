#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CxpathType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CxpathType



namespace CMSD
{

class CxpathType : public TypeBase
{
public:
	CMSD_EXPORT CxpathType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CxpathType(CxpathType const& init);
	void operator=(CxpathType const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_altova_CxpathType); }
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

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CxpathType
