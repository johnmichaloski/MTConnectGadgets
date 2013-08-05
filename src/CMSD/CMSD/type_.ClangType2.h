#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_ClangType2
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_ClangType2



namespace CMSD
{

class ClangType2 : public TypeBase
{
public:
	CMSD_EXPORT ClangType2(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT ClangType2(ClangType2 const& init);
	void operator=(ClangType2 const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_altova_ClangType2); }

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

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_ClangType2
