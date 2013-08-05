#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CAreaUnit
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CAreaUnit



namespace CMSD
{

class CAreaUnit : public TypeBase
{
public:
	CMSD_EXPORT CAreaUnit(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CAreaUnit(CAreaUnit const& init);
	void operator=(CAreaUnit const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_altova_CAreaUnit); }

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

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CAreaUnit
