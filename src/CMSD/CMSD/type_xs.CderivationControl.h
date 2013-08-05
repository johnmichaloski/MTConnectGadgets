#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CderivationControl
#define _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CderivationControl



namespace CMSD
{

namespace xs
{	

class CderivationControl : public TypeBase
{
public:
	CMSD_EXPORT CderivationControl(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CderivationControl(CderivationControl const& init);
	void operator=(CderivationControl const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_CderivationControl); }

	enum EnumValues {
		Invalid = -1,
		k_substitution = 0, // substitution
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

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CderivationControl
