#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CRelaxNGCMSDValidator
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CRelaxNGCMSDValidator



namespace CMSD
{

class CRelaxNGCMSDValidator : public TypeBase
{
public:
	CMSD_EXPORT CRelaxNGCMSDValidator(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CRelaxNGCMSDValidator(CRelaxNGCMSDValidator const& init);
	void operator=(CRelaxNGCMSDValidator const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CRelaxNGCMSDValidator); }
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CRelaxNGCMSDValidator
