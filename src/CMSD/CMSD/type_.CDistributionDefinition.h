#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CDistributionDefinition
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CDistributionDefinition

#include "type_.CUniqueEntity.h"


namespace CMSD
{

class CDistributionDefinition : public ::CMSD::CUniqueEntity
{
public:
	CMSD_EXPORT CDistributionDefinition(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CDistributionDefinition(CDistributionDefinition const& init);
	void operator=(CDistributionDefinition const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CDistributionDefinition); }
	MemberElement<CDistribution, _altova_mi_altova_CDistributionDefinition_altova_Distribution> Distribution;
	struct Distribution { typedef Iterator<CDistribution> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CDistributionDefinition
