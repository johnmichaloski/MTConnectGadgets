#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CprocessContentsType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CprocessContentsType



namespace CMSD
{

namespace xs
{	

class CprocessContentsType : public TypeBase
{
public:
	CMSD_EXPORT CprocessContentsType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CprocessContentsType(CprocessContentsType const& init);
	void operator=(CprocessContentsType const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_CprocessContentsType); }

	enum EnumValues {
		Invalid = -1,
		k_skip = 0, // skip
		k_lax = 1, // lax
		k_strict = 2, // strict
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

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CprocessContentsType
