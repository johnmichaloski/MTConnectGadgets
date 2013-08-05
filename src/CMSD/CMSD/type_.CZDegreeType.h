#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CZDegreeType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CZDegreeType



namespace CMSD
{

class CZDegreeType : public TypeBase
{
public:
	CMSD_EXPORT CZDegreeType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CZDegreeType(CZDegreeType const& init);
	void operator=(CZDegreeType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CZDegreeType); }
	MemberElement<CschemaType, _altova_mi_altova_CZDegreeType_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CZDegreeType
