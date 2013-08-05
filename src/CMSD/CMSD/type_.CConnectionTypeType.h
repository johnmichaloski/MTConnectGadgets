#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CConnectionTypeType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CConnectionTypeType



namespace CMSD
{

class CConnectionTypeType : public TypeBase
{
public:
	CMSD_EXPORT CConnectionTypeType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CConnectionTypeType(CConnectionTypeType const& init);
	void operator=(CConnectionTypeType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CConnectionTypeType); }

	enum EnumValues {
		Invalid = -1,
		k_input = 0, // input
		k_output = 1, // output
		EnumValueCount
	};

	
	CMSD_EXPORT int GetEnumerationValue();
	CMSD_EXPORT void SetEnumerationValue( const int index);
	CMSD_EXPORT void operator=(const string_type& value);
	CMSD_EXPORT operator string_type();
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CConnectionTypeType
