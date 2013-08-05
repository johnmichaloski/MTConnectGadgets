#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CXDegreeType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CXDegreeType



namespace CMSD
{

class CXDegreeType : public TypeBase
{
public:
	CMSD_EXPORT CXDegreeType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CXDegreeType(CXDegreeType const& init);
	void operator=(CXDegreeType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CXDegreeType); }
	MemberElement<CschemaType, _altova_mi_altova_CXDegreeType_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CXDegreeType
