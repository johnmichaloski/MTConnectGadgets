#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CWeightUnitType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CWeightUnitType



namespace CMSD
{

class CWeightUnitType : public TypeBase
{
public:
	CMSD_EXPORT CWeightUnitType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CWeightUnitType(CWeightUnitType const& init);
	void operator=(CWeightUnitType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CWeightUnitType); }

	enum EnumValues {
		Invalid = -1,
		k_ounce = 0, // ounce
		k_pound = 1, // pound
		k_milligram = 2, // milligram
		k_ton = 3, // ton
		k_centigram = 4, // centigram
		k_gram = 5, // gram
		k_kilogram = 6, // kilogram
		EnumValueCount
	};

	
	CMSD_EXPORT int GetEnumerationValue();
	CMSD_EXPORT void SetEnumerationValue( const int index);
	CMSD_EXPORT void operator=(const string_type& value);
	CMSD_EXPORT operator string_type();
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CWeightUnitType
