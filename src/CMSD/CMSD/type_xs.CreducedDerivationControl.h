#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CreducedDerivationControl
#define _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CreducedDerivationControl



namespace CMSD
{

namespace xs
{	

class CreducedDerivationControl : public TypeBase
{
public:
	CMSD_EXPORT CreducedDerivationControl(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CreducedDerivationControl(CreducedDerivationControl const& init);
	void operator=(CreducedDerivationControl const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_CreducedDerivationControl); }

	enum EnumValues {
		Invalid = -1,
		k_extension = 0, // extension
		k_restriction = 1, // restriction
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

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CreducedDerivationControl
