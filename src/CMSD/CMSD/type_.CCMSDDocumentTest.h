#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCMSDDocumentTest
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCMSDDocumentTest



namespace CMSD
{

class CCMSDDocumentTest : public TypeBase
{
public:
	CMSD_EXPORT CCMSDDocumentTest(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CCMSDDocumentTest(CCMSDDocumentTest const& init);
	void operator=(CCMSDDocumentTest const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CCMSDDocumentTest); }
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCMSDDocumentTest
