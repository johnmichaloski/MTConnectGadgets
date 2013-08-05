#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CDistribution
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CDistribution

#include "type_.CNotifyPropertyChangeBase.h"


namespace CMSD
{

class CDistribution : public ::CMSD::CNotifyPropertyChangeBase
{
public:
	CMSD_EXPORT CDistribution(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CDistribution(CDistribution const& init);
	void operator=(CDistribution const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CDistribution); }
	MemberElement<xs::CstringType, _altova_mi_altova_CDistribution_altova_Name> Name;
	struct Name { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CDistribution_altova_Description> Description;
	struct Description { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<CDistributionParameter, _altova_mi_altova_CDistribution_altova_DistributionParameter> DistributionParameter;
	struct DistributionParameter { typedef Iterator<CDistributionParameter> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CDistribution
