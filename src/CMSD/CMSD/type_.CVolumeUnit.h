#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CVolumeUnit
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CVolumeUnit



namespace CMSD
{

class CVolumeUnit : public TypeBase
{
public:
	CMSD_EXPORT CVolumeUnit(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CVolumeUnit(CVolumeUnit const& init);
	void operator=(CVolumeUnit const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_altova_CVolumeUnit); }

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

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CVolumeUnit
