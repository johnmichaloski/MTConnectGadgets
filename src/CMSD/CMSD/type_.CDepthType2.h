#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CDepthType2
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CDepthType2



namespace CMSD
{

class CDepthType2 : public TypeBase
{
public:
	CMSD_EXPORT CDepthType2(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CDepthType2(CDepthType2 const& init);
	void operator=(CDepthType2 const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CDepthType2); }
	MemberElement<CschemaType, _altova_mi_altova_CDepthType2_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CDepthType2
