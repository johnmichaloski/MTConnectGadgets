#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_Ctoken
#define _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_Ctoken



namespace CMSD
{

namespace xs
{	

class Ctoken : public TypeBase
{
public:
	CMSD_EXPORT Ctoken(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT Ctoken(Ctoken const& init);
	void operator=(Ctoken const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_Ctoken); }
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

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_Ctoken
