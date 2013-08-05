#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CTimestampType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CTimestampType



namespace CMSD
{

class CTimestampType : public TypeBase
{
public:
	CMSD_EXPORT CTimestampType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CTimestampType(CTimestampType const& init);
	void operator=(CTimestampType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CTimestampType); }
	MemberElement<CschemaType, _altova_mi_altova_CTimestampType_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CTimestampType
