#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CBaseLocation
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CBaseLocation



namespace CMSD
{

class CBaseLocation : public TypeBase
{
public:
	CMSD_EXPORT CBaseLocation(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CBaseLocation(CBaseLocation const& init);
	void operator=(CBaseLocation const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_altova_CBaseLocation); }

	enum EnumValues {
		Invalid = -1,
		k_floor = 0, // floor
		k_ceiling = 1, // ceiling
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

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CBaseLocation
