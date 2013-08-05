#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CResourceStatusType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CResourceStatusType



namespace CMSD
{

class CResourceStatusType : public TypeBase
{
public:
	CMSD_EXPORT CResourceStatusType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CResourceStatusType(CResourceStatusType const& init);
	void operator=(CResourceStatusType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CResourceStatusType); }

	enum EnumValues {
		Invalid = -1,
		k_busy = 0, // busy
		k_idle = 1, // idle
		k_broken = 2, // broken
		k_underMaintenance = 3, // underMaintenance
		k_unknown = 4, // unknown
		EnumValueCount
	};

	
	CMSD_EXPORT int GetEnumerationValue();
	CMSD_EXPORT void SetEnumerationValue( const int index);
	CMSD_EXPORT void operator=(const string_type& value);
	CMSD_EXPORT operator string_type();
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CResourceStatusType
