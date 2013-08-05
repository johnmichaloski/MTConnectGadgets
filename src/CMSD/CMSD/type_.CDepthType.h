#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CDepthType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CDepthType



namespace CMSD
{

class CDepthType : public TypeBase
{
public:
	CMSD_EXPORT CDepthType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CDepthType(CDepthType const& init);
	void operator=(CDepthType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CDepthType); }
	MemberElement<CschemaType, _altova_mi_altova_CDepthType_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CDepthType
