#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPrecedenceRelationshipType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPrecedenceRelationshipType



namespace CMSD
{

class CPrecedenceRelationshipType : public TypeBase
{
public:
	CMSD_EXPORT CPrecedenceRelationshipType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CPrecedenceRelationshipType(CPrecedenceRelationshipType const& init);
	void operator=(CPrecedenceRelationshipType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CPrecedenceRelationshipType); }

	enum EnumValues {
		Invalid = -1,
		k_SS = 0, // SS
		k_SF = 1, // SF
		k_FS = 2, // FS
		k_FF = 3, // FF
		EnumValueCount
	};

	
	CMSD_EXPORT int GetEnumerationValue();
	CMSD_EXPORT void SetEnumerationValue( const int index);
	CMSD_EXPORT void operator=(const string_type& value);
	CMSD_EXPORT operator string_type();
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPrecedenceRelationshipType
