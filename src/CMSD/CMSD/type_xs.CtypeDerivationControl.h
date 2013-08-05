#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CtypeDerivationControl
#define _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CtypeDerivationControl



namespace CMSD
{

namespace xs
{	

class CtypeDerivationControl : public TypeBase
{
public:
	CMSD_EXPORT CtypeDerivationControl(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CtypeDerivationControl(CtypeDerivationControl const& init);
	void operator=(CtypeDerivationControl const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_CtypeDerivationControl); }

	enum EnumValues {
		Invalid = -1,
		k_extension = 0, // extension
		k_restriction = 1, // restriction
		k_list = 2, // list
		k_union = 3, // union
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

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CtypeDerivationControl
