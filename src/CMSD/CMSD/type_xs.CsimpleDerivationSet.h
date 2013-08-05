#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CsimpleDerivationSet
#define _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CsimpleDerivationSet



namespace CMSD
{

namespace xs
{	

class CsimpleDerivationSet : public TypeBase
{
public:
	CMSD_EXPORT CsimpleDerivationSet(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CsimpleDerivationSet(CsimpleDerivationSet const& init);
	void operator=(CsimpleDerivationSet const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_CsimpleDerivationSet); }

	enum EnumValues {
		Invalid = -1,
		k__all = 0, // #all
		k_list = 1, // list
		k_union = 2, // union
		k_restriction = 3, // restriction
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

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CsimpleDerivationSet
