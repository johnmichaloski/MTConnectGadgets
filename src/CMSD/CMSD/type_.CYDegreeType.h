#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CYDegreeType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CYDegreeType



namespace CMSD
{

class CYDegreeType : public TypeBase
{
public:
	CMSD_EXPORT CYDegreeType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CYDegreeType(CYDegreeType const& init);
	void operator=(CYDegreeType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CYDegreeType); }
	MemberElement<CschemaType, _altova_mi_altova_CYDegreeType_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CYDegreeType
