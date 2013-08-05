#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CLayoutLengthUnitType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CLayoutLengthUnitType



namespace CMSD
{

class CLayoutLengthUnitType : public TypeBase
{
public:
	CMSD_EXPORT CLayoutLengthUnitType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CLayoutLengthUnitType(CLayoutLengthUnitType const& init);
	void operator=(CLayoutLengthUnitType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CLayoutLengthUnitType); }

	enum EnumValues {
		Invalid = -1,
		k_pixel = 0, // pixel
		k_millimeter = 1, // millimeter
		k_centimeter = 2, // centimeter
		k_meter = 3, // meter
		k_kilometer = 4, // kilometer
		k_inch = 5, // inch
		k_foot = 6, // foot
		k_yard = 7, // yard
		k_mile = 8, // mile
		EnumValueCount
	};

	
	CMSD_EXPORT int GetEnumerationValue();
	CMSD_EXPORT void SetEnumerationValue( const int index);
	CMSD_EXPORT void operator=(const string_type& value);
	CMSD_EXPORT operator string_type();
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CLayoutLengthUnitType
