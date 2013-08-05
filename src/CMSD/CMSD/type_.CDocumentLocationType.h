#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CDocumentLocationType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CDocumentLocationType



namespace CMSD
{

class CDocumentLocationType : public TypeBase
{
public:
	CMSD_EXPORT CDocumentLocationType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CDocumentLocationType(CDocumentLocationType const& init);
	void operator=(CDocumentLocationType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CDocumentLocationType); }
	MemberElement<CschemaType, _altova_mi_altova_CDocumentLocationType_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CDocumentLocationType
