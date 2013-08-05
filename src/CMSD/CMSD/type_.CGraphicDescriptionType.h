#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CGraphicDescriptionType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CGraphicDescriptionType



namespace CMSD
{

class CGraphicDescriptionType : public TypeBase
{
public:
	CMSD_EXPORT CGraphicDescriptionType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CGraphicDescriptionType(CGraphicDescriptionType const& init);
	void operator=(CGraphicDescriptionType const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_altova_CGraphicDescriptionType); }

	enum EnumValues {
		Invalid = -1,
		k_modelGraphic = 0, // modelGraphic
		k_imageGraphic = 1, // imageGraphic
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

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CGraphicDescriptionType
