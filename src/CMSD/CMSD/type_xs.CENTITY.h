#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CENTITY
#define _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CENTITY



namespace CMSD
{

namespace xs
{	

class CENTITY : public TypeBase
{
public:
	CMSD_EXPORT CENTITY(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CENTITY(CENTITY const& init);
	void operator=(CENTITY const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_CENTITY); }
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

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CENTITY
