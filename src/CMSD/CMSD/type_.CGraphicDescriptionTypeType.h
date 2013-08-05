#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CGraphicDescriptionTypeType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CGraphicDescriptionTypeType



namespace CMSD
{

class CGraphicDescriptionTypeType : public TypeBase
{
public:
	CMSD_EXPORT CGraphicDescriptionTypeType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CGraphicDescriptionTypeType(CGraphicDescriptionTypeType const& init);
	void operator=(CGraphicDescriptionTypeType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CGraphicDescriptionTypeType); }

	enum EnumValues {
		Invalid = -1,
		k_modelGraphic = 0, // modelGraphic
		k_imageGraphic = 1, // imageGraphic
		EnumValueCount
	};

	
	CMSD_EXPORT int GetEnumerationValue();
	CMSD_EXPORT void SetEnumerationValue( const int index);
	CMSD_EXPORT void operator=(const string_type& value);
	CMSD_EXPORT operator string_type();
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CGraphicDescriptionTypeType
