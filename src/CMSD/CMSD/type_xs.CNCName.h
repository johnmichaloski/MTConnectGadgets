#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CNCName
#define _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CNCName



namespace CMSD
{

namespace xs
{	

class CNCName : public TypeBase
{
public:
	CMSD_EXPORT CNCName(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CNCName(CNCName const& init);
	void operator=(CNCName const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_CNCName); }
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

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CNCName
