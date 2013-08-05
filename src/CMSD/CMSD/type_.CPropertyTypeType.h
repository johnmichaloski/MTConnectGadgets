#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPropertyTypeType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPropertyTypeType



namespace CMSD
{

class CPropertyTypeType : public TypeBase
{
public:
	CMSD_EXPORT CPropertyTypeType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CPropertyTypeType(CPropertyTypeType const& init);
	void operator=(CPropertyTypeType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CPropertyTypeType); }

	enum EnumValues {
		Invalid = -1,
		k_simple = 0, // simple
		k_reference = 1, // reference
		k_stochastic = 2, // stochastic
		EnumValueCount
	};

	
	CMSD_EXPORT int GetEnumerationValue();
	CMSD_EXPORT void SetEnumerationValue( const int index);
	CMSD_EXPORT void operator=(const string_type& value);
	CMSD_EXPORT operator string_type();
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPropertyTypeType
