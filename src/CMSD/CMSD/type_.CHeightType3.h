#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CHeightType3
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CHeightType3



namespace CMSD
{

class CHeightType3 : public TypeBase
{
public:
	CMSD_EXPORT CHeightType3(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CHeightType3(CHeightType3 const& init);
	void operator=(CHeightType3 const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CHeightType3); }
	MemberElement<CschemaType, _altova_mi_altova_CHeightType3_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CHeightType3
