#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CTextAnchorLocationType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CTextAnchorLocationType



namespace CMSD
{

class CTextAnchorLocationType : public TypeBase
{
public:
	CMSD_EXPORT CTextAnchorLocationType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CTextAnchorLocationType(CTextAnchorLocationType const& init);
	void operator=(CTextAnchorLocationType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CTextAnchorLocationType); }

	enum EnumValues {
		Invalid = -1,
		k_upperLeft = 0, // upperLeft
		k_center = 1, // center
		EnumValueCount
	};

	
	CMSD_EXPORT int GetEnumerationValue();
	CMSD_EXPORT void SetEnumerationValue( const int index);
	CMSD_EXPORT void operator=(const string_type& value);
	CMSD_EXPORT operator string_type();
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CTextAnchorLocationType
