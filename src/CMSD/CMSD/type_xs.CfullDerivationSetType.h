#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CfullDerivationSetType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CfullDerivationSetType



namespace CMSD
{

namespace xs
{	

class CfullDerivationSetType : public TypeBase
{
public:
	CMSD_EXPORT CfullDerivationSetType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CfullDerivationSetType(CfullDerivationSetType const& init);
	void operator=(CfullDerivationSetType const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_CfullDerivationSetType); }

	enum EnumValues {
		Invalid = -1,
		k__all = 0, // #all
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

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CfullDerivationSetType
