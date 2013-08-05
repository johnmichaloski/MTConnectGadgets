#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CmemberTypesType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CmemberTypesType



namespace CMSD
{

class CmemberTypesType : public TypeBase
{
public:
	CMSD_EXPORT CmemberTypesType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CmemberTypesType(CmemberTypesType const& init);
	void operator=(CmemberTypesType const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_altova_CmemberTypesType); }
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

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CmemberTypesType
