#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CResourceType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CResourceType



namespace CMSD
{

class CResourceType : public TypeBase
{
public:
	CMSD_EXPORT CResourceType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CResourceType(CResourceType const& init);
	void operator=(CResourceType const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_altova_CResourceType); }

	enum EnumValues {
		Invalid = -1,
		k_carrier = 0, // carrier
		k_conveyor = 1, // conveyor
		k_crane = 2, // crane
		k_employee = 3, // employee
		k_fixture = 4, // fixture
		k_machine = 5, // machine
		k_path = 6, // path
		k_powerAndFree = 7, // powerAndFree
		k_station = 8, // station
		k_tool = 9, // tool
		k_transporter = 10, // transporter
		k_other = 11, // other
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

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CResourceType
