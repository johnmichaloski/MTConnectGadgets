#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CSpeedUnit
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CSpeedUnit



namespace CMSD
{

class CSpeedUnit : public TypeBase
{
public:
	CMSD_EXPORT CSpeedUnit(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CSpeedUnit(CSpeedUnit const& init);
	void operator=(CSpeedUnit const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_altova_CSpeedUnit); }

	enum EnumValues {
		Invalid = -1,
		k_footPerSecond = 0, // footPerSecond
		k_kilometerPerHour = 1, // kilometerPerHour
		k_meterPerSecond = 2, // meterPerSecond
		k_milePerHour = 3, // milePerHour
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

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CSpeedUnit
