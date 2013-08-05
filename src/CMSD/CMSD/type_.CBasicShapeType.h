#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CBasicShapeType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CBasicShapeType



namespace CMSD
{

class CBasicShapeType : public TypeBase
{
public:
	CMSD_EXPORT CBasicShapeType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CBasicShapeType(CBasicShapeType const& init);
	void operator=(CBasicShapeType const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_altova_CBasicShapeType); }

	enum EnumValues {
		Invalid = -1,
		k_box = 0, // box
		k_circle = 1, // circle
		k_polygon = 2, // polygon
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

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CBasicShapeType
