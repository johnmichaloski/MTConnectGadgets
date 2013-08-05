#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CProcessGroupTypeType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CProcessGroupTypeType



namespace CMSD
{

class CProcessGroupTypeType : public TypeBase
{
public:
	CMSD_EXPORT CProcessGroupTypeType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CProcessGroupTypeType(CProcessGroupTypeType const& init);
	void operator=(CProcessGroupTypeType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CProcessGroupTypeType); }

	enum EnumValues {
		Invalid = -1,
		k_sequence = 0, // sequence
		k_concurrent = 1, // concurrent
		k_decision = 2, // decision
		EnumValueCount
	};

	
	CMSD_EXPORT int GetEnumerationValue();
	CMSD_EXPORT void SetEnumerationValue( const int index);
	CMSD_EXPORT void operator=(const string_type& value);
	CMSD_EXPORT operator string_type();
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CProcessGroupTypeType
