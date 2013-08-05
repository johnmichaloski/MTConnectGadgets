#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CHeightType2
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CHeightType2



namespace CMSD
{

class CHeightType2 : public TypeBase
{
public:
	CMSD_EXPORT CHeightType2(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CHeightType2(CHeightType2 const& init);
	void operator=(CHeightType2 const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CHeightType2); }
	MemberElement<CschemaType, _altova_mi_altova_CHeightType2_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CHeightType2
