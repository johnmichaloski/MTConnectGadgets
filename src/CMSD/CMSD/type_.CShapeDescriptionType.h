#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CShapeDescriptionType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CShapeDescriptionType



namespace CMSD
{

class CShapeDescriptionType : public TypeBase
{
public:
	CMSD_EXPORT CShapeDescriptionType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CShapeDescriptionType(CShapeDescriptionType const& init);
	void operator=(CShapeDescriptionType const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_altova_CShapeDescriptionType); }

	enum EnumValues {
		Invalid = -1,
		k_basic = 0, // basic
		k_graphic = 1, // graphic
		k_segment = 2, // segment
		k_text = 3, // text
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

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CShapeDescriptionType
