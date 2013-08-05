#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CReleaseDateType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CReleaseDateType



namespace CMSD
{

class CReleaseDateType : public TypeBase
{
public:
	CMSD_EXPORT CReleaseDateType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CReleaseDateType(CReleaseDateType const& init);
	void operator=(CReleaseDateType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CReleaseDateType); }
	MemberElement<CschemaType, _altova_mi_altova_CReleaseDateType_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CReleaseDateType
