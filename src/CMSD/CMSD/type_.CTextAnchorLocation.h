#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CTextAnchorLocation
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CTextAnchorLocation



namespace CMSD
{

class CTextAnchorLocation : public TypeBase
{
public:
	CMSD_EXPORT CTextAnchorLocation(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CTextAnchorLocation(CTextAnchorLocation const& init);
	void operator=(CTextAnchorLocation const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_altova_CTextAnchorLocation); }

	enum EnumValues {
		Invalid = -1,
		k_upperLeft = 0, // upperLeft
		k_center = 1, // center
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

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CTextAnchorLocation
