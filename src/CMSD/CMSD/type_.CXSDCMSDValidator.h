#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CXSDCMSDValidator
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CXSDCMSDValidator



namespace CMSD
{

class CXSDCMSDValidator : public TypeBase
{
public:
	CMSD_EXPORT CXSDCMSDValidator(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CXSDCMSDValidator(CXSDCMSDValidator const& init);
	void operator=(CXSDCMSDValidator const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CXSDCMSDValidator); }
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CXSDCMSDValidator
