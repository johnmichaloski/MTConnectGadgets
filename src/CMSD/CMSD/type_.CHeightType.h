#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CHeightType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CHeightType



namespace CMSD
{

class CHeightType : public TypeBase
{
public:
	CMSD_EXPORT CHeightType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CHeightType(CHeightType const& init);
	void operator=(CHeightType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CHeightType); }
	MemberElement<CschemaType, _altova_mi_altova_CHeightType_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CHeightType
