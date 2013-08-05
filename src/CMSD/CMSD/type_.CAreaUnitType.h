#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CAreaUnitType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CAreaUnitType



namespace CMSD
{

class CAreaUnitType : public TypeBase
{
public:
	CMSD_EXPORT CAreaUnitType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CAreaUnitType(CAreaUnitType const& init);
	void operator=(CAreaUnitType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CAreaUnitType); }

	enum EnumValues {
		Invalid = -1,
		k_squareInch = 0, // squareInch
		k_squareFoot = 1, // squareFoot
		k_squareYard = 2, // squareYard
		k_squareCentimeter = 3, // squareCentimeter
		k_squareMeter = 4, // squareMeter
		k_squareKilometer = 5, // squareKilometer
		k_squareMile = 6, // squareMile
		EnumValueCount
	};

	
	CMSD_EXPORT int GetEnumerationValue();
	CMSD_EXPORT void SetEnumerationValue( const int index);
	CMSD_EXPORT void operator=(const string_type& value);
	CMSD_EXPORT operator string_type();
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CAreaUnitType
