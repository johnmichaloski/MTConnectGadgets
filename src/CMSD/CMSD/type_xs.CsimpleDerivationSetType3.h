#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CsimpleDerivationSetType3
#define _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CsimpleDerivationSetType3



namespace CMSD
{

namespace xs
{	

class CsimpleDerivationSetType3 : public TypeBase
{
public:
	CMSD_EXPORT CsimpleDerivationSetType3(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CsimpleDerivationSetType3(CsimpleDerivationSetType3 const& init);
	void operator=(CsimpleDerivationSetType3 const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_CsimpleDerivationSetType3); }

	enum EnumValues {
		Invalid = -1,
		k_list = 0, // list
		k_union = 1, // union
		k_restriction = 2, // restriction
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

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CsimpleDerivationSetType3
