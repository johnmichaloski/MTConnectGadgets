#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CDepthType3
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CDepthType3



namespace CMSD
{

class CDepthType3 : public TypeBase
{
public:
	CMSD_EXPORT CDepthType3(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CDepthType3(CDepthType3 const& init);
	void operator=(CDepthType3 const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CDepthType3); }
	MemberElement<CschemaType, _altova_mi_altova_CDepthType3_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CDepthType3
