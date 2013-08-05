#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCoordinateSystem
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCoordinateSystem



namespace CMSD
{

class CCoordinateSystem : public TypeBase
{
public:
	CMSD_EXPORT CCoordinateSystem(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CCoordinateSystem(CCoordinateSystem const& init);
	void operator=(CCoordinateSystem const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_altova_CCoordinateSystem); }

	enum EnumValues {
		Invalid = -1,
		k_upperLeftBased = 0, // upperLeftBased
		k_centerBased = 1, // centerBased
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

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCoordinateSystem
