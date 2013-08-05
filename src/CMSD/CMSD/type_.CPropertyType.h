#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPropertyType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPropertyType



namespace CMSD
{

class CPropertyType : public TypeBase
{
public:
	CMSD_EXPORT CPropertyType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CPropertyType(CPropertyType const& init);
	void operator=(CPropertyType const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_altova_CPropertyType); }

	enum EnumValues {
		Invalid = -1,
		k_simple = 0, // simple
		k_reference = 1, // reference
		k_stochastic = 2, // stochastic
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


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPropertyType
