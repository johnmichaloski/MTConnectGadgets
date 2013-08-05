#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_ClangType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_ClangType



namespace CMSD
{

class ClangType : public TypeBase
{
public:
	CMSD_EXPORT ClangType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT ClangType(ClangType const& init);
	void operator=(ClangType const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_altova_ClangType); }

	enum EnumValues {
		Invalid = -1,
		k_ = 0, // 
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

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_ClangType
