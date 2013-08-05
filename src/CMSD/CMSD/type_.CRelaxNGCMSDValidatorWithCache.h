#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CRelaxNGCMSDValidatorWithCache
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CRelaxNGCMSDValidatorWithCache



namespace CMSD
{

class CRelaxNGCMSDValidatorWithCache : public TypeBase
{
public:
	CMSD_EXPORT CRelaxNGCMSDValidatorWithCache(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CRelaxNGCMSDValidatorWithCache(CRelaxNGCMSDValidatorWithCache const& init);
	void operator=(CRelaxNGCMSDValidatorWithCache const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CRelaxNGCMSDValidatorWithCache); }
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CRelaxNGCMSDValidatorWithCache
