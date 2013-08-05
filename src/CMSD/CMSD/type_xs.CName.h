#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CName
#define _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CName



namespace CMSD
{

namespace xs
{	

class CName : public TypeBase
{
public:
	CMSD_EXPORT CName(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CName(CName const& init);
	void operator=(CName const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_CName); }
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

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CName
