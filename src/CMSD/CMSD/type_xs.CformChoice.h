#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CformChoice
#define _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CformChoice



namespace CMSD
{

namespace xs
{	

class CformChoice : public TypeBase
{
public:
	CMSD_EXPORT CformChoice(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CformChoice(CformChoice const& init);
	void operator=(CformChoice const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_CformChoice); }

	enum EnumValues {
		Invalid = -1,
		k_qualified = 0, // qualified
		k_unqualified = 1, // unqualified
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



} // namespace xs

}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CformChoice
