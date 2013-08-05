#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CXType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CXType



namespace CMSD
{

class CXType : public TypeBase
{
public:
	CMSD_EXPORT CXType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CXType(CXType const& init);
	void operator=(CXType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CXType); }
	MemberElement<CschemaType, _altova_mi_altova_CXType_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CXType
