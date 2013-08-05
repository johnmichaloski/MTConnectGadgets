#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CStochasticProperty
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CStochasticProperty

#include "type_.CNotifyPropertyChangeBase.h"


namespace CMSD
{

class CStochasticProperty : public ::CMSD::CNotifyPropertyChangeBase
{
public:
	CMSD_EXPORT CStochasticProperty(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CStochasticProperty(CStochasticProperty const& init);
	void operator=(CStochasticProperty const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CStochasticProperty); }
	MemberElement<CDistribution, _altova_mi_altova_CStochasticProperty_altova_Distribution> Distribution;
	struct Distribution { typedef Iterator<CDistribution> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CStochasticProperty
