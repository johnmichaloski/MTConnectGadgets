#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCostTypeType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCostTypeType



namespace CMSD
{

class CCostTypeType : public TypeBase
{
public:
	CMSD_EXPORT CCostTypeType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CCostTypeType(CCostTypeType const& init);
	void operator=(CCostTypeType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CCostTypeType); }

	enum EnumValues {
		Invalid = -1,
		k_fixed = 0, // fixed
		k_variable = 1, // variable
		EnumValueCount
	};

	
	CMSD_EXPORT int GetEnumerationValue();
	CMSD_EXPORT void SetEnumerationValue( const int index);
	CMSD_EXPORT void operator=(const string_type& value);
	CMSD_EXPORT operator string_type();
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCostTypeType
