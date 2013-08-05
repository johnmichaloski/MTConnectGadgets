#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CBasicShapeTypeType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CBasicShapeTypeType



namespace CMSD
{

class CBasicShapeTypeType : public TypeBase
{
public:
	CMSD_EXPORT CBasicShapeTypeType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CBasicShapeTypeType(CBasicShapeTypeType const& init);
	void operator=(CBasicShapeTypeType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CBasicShapeTypeType); }

	enum EnumValues {
		Invalid = -1,
		k_box = 0, // box
		k_circle = 1, // circle
		k_polygon = 2, // polygon
		EnumValueCount
	};

	
	CMSD_EXPORT int GetEnumerationValue();
	CMSD_EXPORT void SetEnumerationValue( const int index);
	CMSD_EXPORT void operator=(const string_type& value);
	CMSD_EXPORT operator string_type();
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CBasicShapeTypeType
