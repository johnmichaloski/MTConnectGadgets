#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CDuration
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CDuration

#include "type_.CNotifyPropertyChangeBase.h"


namespace CMSD
{

class CDuration : public ::CMSD::CNotifyPropertyChangeBase
{
public:
	CMSD_EXPORT CDuration(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CDuration(CDuration const& init);
	void operator=(CDuration const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CDuration); }
	MemberElement<CTimeUnitType, _altova_mi_altova_CDuration_altova_Unit> Unit;
	struct Unit { typedef Iterator<CTimeUnitType> iterator; };
	MemberElement<CValueType4, _altova_mi_altova_CDuration_altova_Value2> Value2;
	struct Value2 { typedef Iterator<CValueType4> iterator; };
	MemberElement<CDistribution, _altova_mi_altova_CDuration_altova_Distribution> Distribution;
	struct Distribution { typedef Iterator<CDistribution> iterator; };
	MemberElement<CDistributionDefinitionReference, _altova_mi_altova_CDuration_altova_DistributionReference> DistributionReference;
	struct DistributionReference { typedef Iterator<CDistributionDefinitionReference> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CDuration
