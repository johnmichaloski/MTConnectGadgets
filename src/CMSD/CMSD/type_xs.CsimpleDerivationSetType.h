#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CsimpleDerivationSetType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CsimpleDerivationSetType



namespace CMSD
{

namespace xs
{	

class CsimpleDerivationSetType : public TypeBase
{
public:
	CMSD_EXPORT CsimpleDerivationSetType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CsimpleDerivationSetType(CsimpleDerivationSetType const& init);
	void operator=(CsimpleDerivationSetType const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_CsimpleDerivationSetType); }

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

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CsimpleDerivationSetType
