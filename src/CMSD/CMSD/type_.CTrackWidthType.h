#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CTrackWidthType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CTrackWidthType



namespace CMSD
{

class CTrackWidthType : public TypeBase
{
public:
	CMSD_EXPORT CTrackWidthType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CTrackWidthType(CTrackWidthType const& init);
	void operator=(CTrackWidthType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CTrackWidthType); }
	MemberElement<CschemaType, _altova_mi_altova_CTrackWidthType_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CTrackWidthType
