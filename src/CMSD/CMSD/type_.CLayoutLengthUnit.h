#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CLayoutLengthUnit
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CLayoutLengthUnit



namespace CMSD
{

class CLayoutLengthUnit : public TypeBase
{
public:
	CMSD_EXPORT CLayoutLengthUnit(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CLayoutLengthUnit(CLayoutLengthUnit const& init);
	void operator=(CLayoutLengthUnit const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_altova_CLayoutLengthUnit); }

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
	void operator= (const string_type& value) 
	{
		altova::XmlFormatter* Formatter = static_cast<altova::XmlFormatter*>(altova::AnySimpleTypeFormatter);
		MsxmlTreeOperations::SetValue(GetNode(), Formatter->Format(value));
	}	
		
	operator string_type()
	{
		return CastAs<string_type >::Do(GetNode(), 0);
	}
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CLayoutLengthUnit
