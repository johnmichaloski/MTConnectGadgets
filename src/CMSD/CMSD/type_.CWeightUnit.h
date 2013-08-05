#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CWeightUnit
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CWeightUnit



namespace CMSD
{

class CWeightUnit : public TypeBase
{
public:
	CMSD_EXPORT CWeightUnit(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CWeightUnit(CWeightUnit const& init);
	void operator=(CWeightUnit const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_altova_CWeightUnit); }

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

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CWeightUnit
