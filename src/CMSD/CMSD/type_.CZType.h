#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CZType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CZType



namespace CMSD
{

class CZType : public TypeBase
{
public:
	CMSD_EXPORT CZType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CZType(CZType const& init);
	void operator=(CZType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CZType); }
	MemberElement<CschemaType, _altova_mi_altova_CZType_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CZType
