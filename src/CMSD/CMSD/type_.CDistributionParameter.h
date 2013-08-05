#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CDistributionParameter
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CDistributionParameter

#include "type_.CNotifyPropertyChangeBase.h"


namespace CMSD
{

class CDistributionParameter : public ::CMSD::CNotifyPropertyChangeBase
{
public:
	CMSD_EXPORT CDistributionParameter(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CDistributionParameter(CDistributionParameter const& init);
	void operator=(CDistributionParameter const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CDistributionParameter); }
	MemberElement<xs::CstringType, _altova_mi_altova_CDistributionParameter_altova_Name> Name;
	struct Name { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CDistributionParameter_altova_Description> Description;
	struct Description { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<CValueType3, _altova_mi_altova_CDistributionParameter_altova_Value2> Value2;
	struct Value2 { typedef Iterator<CValueType3> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CDistributionParameter
