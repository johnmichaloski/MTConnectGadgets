#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CMaximumType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CMaximumType



namespace CMSD
{

class CMaximumType : public TypeBase
{
public:
	CMSD_EXPORT CMaximumType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CMaximumType(CMaximumType const& init);
	void operator=(CMaximumType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CMaximumType); }
	MemberElement<CschemaType, _altova_mi_altova_CMaximumType_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CMaximumType
