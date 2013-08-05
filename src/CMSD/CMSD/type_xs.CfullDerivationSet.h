#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CfullDerivationSet
#define _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CfullDerivationSet



namespace CMSD
{

namespace xs
{	

class CfullDerivationSet : public TypeBase
{
public:
	CMSD_EXPORT CfullDerivationSet(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CfullDerivationSet(CfullDerivationSet const& init);
	void operator=(CfullDerivationSet const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_CfullDerivationSet); }

	enum EnumValues {
		Invalid = -1,
		k__all = 0, // #all
		k_extension = 1, // extension
		k_restriction = 2, // restriction
		k_list = 3, // list
		k_union = 4, // union
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

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CfullDerivationSet
