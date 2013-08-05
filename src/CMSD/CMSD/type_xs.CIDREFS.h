#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CIDREFS
#define _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CIDREFS



namespace CMSD
{

namespace xs
{	

class CIDREFS : public TypeBase
{
public:
	CMSD_EXPORT CIDREFS(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CIDREFS(CIDREFS const& init);
	void operator=(CIDREFS const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_CIDREFS); }
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



} // namespace xs

}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CIDREFS
