#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCostCategoryType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCostCategoryType



namespace CMSD
{

class CCostCategoryType : public TypeBase
{
public:
	CMSD_EXPORT CCostCategoryType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CCostCategoryType(CCostCategoryType const& init);
	void operator=(CCostCategoryType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CCostCategoryType); }

	enum EnumValues {
		Invalid = -1,
		k_indirect = 0, // indirect
		k_labor = 1, // labor
		k_material = 2, // material
		k_equipment = 3, // equipment
		k_other = 4, // other
		EnumValueCount
	};

	
	CMSD_EXPORT int GetEnumerationValue();
	CMSD_EXPORT void SetEnumerationValue( const int index);
	CMSD_EXPORT void operator=(const string_type& value);
	CMSD_EXPORT operator string_type();
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCostCategoryType
