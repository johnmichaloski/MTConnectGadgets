#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CInventoryItemType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CInventoryItemType



namespace CMSD
{

class CInventoryItemType : public TypeBase
{
public:
	CMSD_EXPORT CInventoryItemType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CInventoryItemType(CInventoryItemType const& init);
	void operator=(CInventoryItemType const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_altova_CInventoryItemType); }

	enum EnumValues {
		Invalid = -1,
		k_part = 0, // part
		k_resource = 1, // resource
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

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CInventoryItemType
