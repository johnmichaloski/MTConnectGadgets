#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CJobStatusType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CJobStatusType



namespace CMSD
{

class CJobStatusType : public TypeBase
{
public:
	CMSD_EXPORT CJobStatusType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CJobStatusType(CJobStatusType const& init);
	void operator=(CJobStatusType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CJobStatusType); }

	enum EnumValues {
		Invalid = -1,
		k_released = 0, // released
		k_started = 1, // started
		k_unknown = 2, // unknown
		k_completed = 3, // completed
		k_cancelled = 4, // cancelled
		k_blocked = 5, // blocked
		EnumValueCount
	};

	
	CMSD_EXPORT int GetEnumerationValue();
	CMSD_EXPORT void SetEnumerationValue( const int index);
	CMSD_EXPORT void operator=(const string_type& value);
	CMSD_EXPORT operator string_type();
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CJobStatusType
