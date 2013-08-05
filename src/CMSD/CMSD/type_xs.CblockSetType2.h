#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CblockSetType2
#define _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CblockSetType2



namespace CMSD
{

namespace xs
{	

class CblockSetType2 : public TypeBase
{
public:
	CMSD_EXPORT CblockSetType2(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CblockSetType2(CblockSetType2 const& init);
	void operator=(CblockSetType2 const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_CblockSetType2); }

	enum EnumValues {
		Invalid = -1,
		k_extension = 0, // extension
		k_restriction = 1, // restriction
		k_substitution = 2, // substitution
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

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CblockSetType2
