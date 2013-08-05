#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCoordinateSystemType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCoordinateSystemType



namespace CMSD
{

class CCoordinateSystemType : public TypeBase
{
public:
	CMSD_EXPORT CCoordinateSystemType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CCoordinateSystemType(CCoordinateSystemType const& init);
	void operator=(CCoordinateSystemType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CCoordinateSystemType); }

	enum EnumValues {
		Invalid = -1,
		k_upperLeftBased = 0, // upperLeftBased
		k_centerBased = 1, // centerBased
		EnumValueCount
	};

	
	CMSD_EXPORT int GetEnumerationValue();
	CMSD_EXPORT void SetEnumerationValue( const int index);
	CMSD_EXPORT void operator=(const string_type& value);
	CMSD_EXPORT operator string_type();
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCoordinateSystemType
