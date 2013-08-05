#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CBaseLocationType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CBaseLocationType



namespace CMSD
{

class CBaseLocationType : public TypeBase
{
public:
	CMSD_EXPORT CBaseLocationType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CBaseLocationType(CBaseLocationType const& init);
	void operator=(CBaseLocationType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CBaseLocationType); }

	enum EnumValues {
		Invalid = -1,
		k_floor = 0, // floor
		k_ceiling = 1, // ceiling
		EnumValueCount
	};

	
	CMSD_EXPORT int GetEnumerationValue();
	CMSD_EXPORT void SetEnumerationValue( const int index);
	CMSD_EXPORT void operator=(const string_type& value);
	CMSD_EXPORT operator string_type();
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CBaseLocationType
