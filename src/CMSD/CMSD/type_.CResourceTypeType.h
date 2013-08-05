#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CResourceTypeType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CResourceTypeType



namespace CMSD
{

class CResourceTypeType : public TypeBase
{
public:
	CMSD_EXPORT CResourceTypeType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CResourceTypeType(CResourceTypeType const& init);
	void operator=(CResourceTypeType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CResourceTypeType); }

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

	
	CMSD_EXPORT int GetEnumerationValue();
	CMSD_EXPORT void SetEnumerationValue( const int index);
	CMSD_EXPORT void operator=(const string_type& value);
	CMSD_EXPORT operator string_type();
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CResourceTypeType
