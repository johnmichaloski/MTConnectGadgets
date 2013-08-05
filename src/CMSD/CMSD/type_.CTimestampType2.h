#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CTimestampType2
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CTimestampType2



namespace CMSD
{

class CTimestampType2 : public TypeBase
{
public:
	CMSD_EXPORT CTimestampType2(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CTimestampType2(CTimestampType2 const& init);
	void operator=(CTimestampType2 const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CTimestampType2); }
	MemberElement<CschemaType, _altova_mi_altova_CTimestampType2_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CTimestampType2
