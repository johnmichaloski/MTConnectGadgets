#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CVolumeUnitType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CVolumeUnitType



namespace CMSD
{

class CVolumeUnitType : public TypeBase
{
public:
	CMSD_EXPORT CVolumeUnitType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CVolumeUnitType(CVolumeUnitType const& init);
	void operator=(CVolumeUnitType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CVolumeUnitType); }

	enum EnumValues {
		Invalid = -1,
		k_cubicCentimeter = 0, // cubicCentimeter
		k_cubicInch = 1, // cubicInch
		k_cubicFoot = 2, // cubicFoot
		k_cubicMeter = 3, // cubicMeter
		k_cubicYard = 4, // cubicYard
		k_milliliter = 5, // milliliter
		k_gallon = 6, // gallon
		k_liter = 7, // liter
		k_pint = 8, // pint
		k_quart = 9, // quart
		k_ounce = 10, // ounce
		EnumValueCount
	};

	
	CMSD_EXPORT int GetEnumerationValue();
	CMSD_EXPORT void SetEnumerationValue( const int index);
	CMSD_EXPORT void operator=(const string_type& value);
	CMSD_EXPORT operator string_type();
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CVolumeUnitType
