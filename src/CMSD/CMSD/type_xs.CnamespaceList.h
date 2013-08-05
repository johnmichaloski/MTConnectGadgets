#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CnamespaceList
#define _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CnamespaceList



namespace CMSD
{

namespace xs
{	

class CnamespaceList : public TypeBase
{
public:
	CMSD_EXPORT CnamespaceList(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CnamespaceList(CnamespaceList const& init);
	void operator=(CnamespaceList const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_CnamespaceList); }

	enum EnumValues {
		Invalid = -1,
		k___any = 0, // ##any
		k___other = 1, // ##other
		k___targetNamespace = 2, // ##targetNamespace
		k___local = 3, // ##local
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

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CnamespaceList
