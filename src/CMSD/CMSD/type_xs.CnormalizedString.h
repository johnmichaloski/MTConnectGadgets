#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CnormalizedString
#define _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CnormalizedString



namespace CMSD
{

namespace xs
{	

class CnormalizedString : public TypeBase
{
public:
	CMSD_EXPORT CnormalizedString(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CnormalizedString(CnormalizedString const& init);
	void operator=(CnormalizedString const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_CnormalizedString); }
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

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CnormalizedString
