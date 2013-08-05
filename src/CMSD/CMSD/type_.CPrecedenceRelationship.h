#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPrecedenceRelationship
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPrecedenceRelationship



namespace CMSD
{

class CPrecedenceRelationship : public TypeBase
{
public:
	CMSD_EXPORT CPrecedenceRelationship(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CPrecedenceRelationship(CPrecedenceRelationship const& init);
	void operator=(CPrecedenceRelationship const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_altova_CPrecedenceRelationship); }

	enum EnumValues {
		Invalid = -1,
		k_SS = 0, // SS
		k_SF = 1, // SF
		k_FS = 2, // FS
		k_FF = 3, // FF
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

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPrecedenceRelationship
