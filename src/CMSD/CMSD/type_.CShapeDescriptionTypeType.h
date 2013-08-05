#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CShapeDescriptionTypeType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CShapeDescriptionTypeType



namespace CMSD
{

class CShapeDescriptionTypeType : public TypeBase
{
public:
	CMSD_EXPORT CShapeDescriptionTypeType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CShapeDescriptionTypeType(CShapeDescriptionTypeType const& init);
	void operator=(CShapeDescriptionTypeType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CShapeDescriptionTypeType); }

	enum EnumValues {
		Invalid = -1,
		k_basic = 0, // basic
		k_graphic = 1, // graphic
		k_segment = 2, // segment
		k_text = 3, // text
		EnumValueCount
	};

	
	CMSD_EXPORT int GetEnumerationValue();
	CMSD_EXPORT void SetEnumerationValue( const int index);
	CMSD_EXPORT void operator=(const string_type& value);
	CMSD_EXPORT operator string_type();
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CShapeDescriptionTypeType
