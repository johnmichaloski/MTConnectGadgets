#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CnamespaceListType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CnamespaceListType



namespace CMSD
{

namespace xs
{	

class CnamespaceListType : public TypeBase
{
public:
	CMSD_EXPORT CnamespaceListType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CnamespaceListType(CnamespaceListType const& init);
	void operator=(CnamespaceListType const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_CnamespaceListType); }

	enum EnumValues {
		Invalid = -1,
		k___any = 0, // ##any
		k___other = 1, // ##other
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

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CnamespaceListType
