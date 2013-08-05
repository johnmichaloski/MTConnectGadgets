#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CnamespaceListType4
#define _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CnamespaceListType4



namespace CMSD
{

namespace xs
{	

class CnamespaceListType4 : public TypeBase
{
public:
	CMSD_EXPORT CnamespaceListType4(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CnamespaceListType4(CnamespaceListType4 const& init);
	void operator=(CnamespaceListType4 const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_CnamespaceListType4); }

	enum EnumValues {
		Invalid = -1,
		k___targetNamespace = 0, // ##targetNamespace
		k___local = 1, // ##local
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

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CnamespaceListType4
