#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CSegmentTypeType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CSegmentTypeType



namespace CMSD
{

class CSegmentTypeType : public TypeBase
{
public:
	CMSD_EXPORT CSegmentTypeType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CSegmentTypeType(CSegmentTypeType const& init);
	void operator=(CSegmentTypeType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CSegmentTypeType); }

	enum EnumValues {
		Invalid = -1,
		k_straight = 0, // straight
		k_curved = 1, // curved
		EnumValueCount
	};

	
	CMSD_EXPORT int GetEnumerationValue();
	CMSD_EXPORT void SetEnumerationValue( const int index);
	CMSD_EXPORT void operator=(const string_type& value);
	CMSD_EXPORT operator string_type();
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CSegmentTypeType
