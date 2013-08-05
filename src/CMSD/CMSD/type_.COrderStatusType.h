#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_COrderStatusType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_COrderStatusType



namespace CMSD
{

class COrderStatusType : public TypeBase
{
public:
	CMSD_EXPORT COrderStatusType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT COrderStatusType(COrderStatusType const& init);
	void operator=(COrderStatusType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_COrderStatusType); }

	enum EnumValues {
		Invalid = -1,
		k_unknown = 0, // unknown
		k_created = 1, // created
		k_released = 2, // released
		k_completed = 3, // completed
		k_shipped = 4, // shipped
		k_cancelled = 5, // cancelled
		EnumValueCount
	};

	
	CMSD_EXPORT int GetEnumerationValue();
	CMSD_EXPORT void SetEnumerationValue( const int index);
	CMSD_EXPORT void operator=(const string_type& value);
	CMSD_EXPORT operator string_type();
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_COrderStatusType
