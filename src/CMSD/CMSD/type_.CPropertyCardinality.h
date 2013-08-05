#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPropertyCardinality
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPropertyCardinality

#include "type_.CNotifyPropertyChangeBase.h"


namespace CMSD
{

class CPropertyCardinality : public ::CMSD::CNotifyPropertyChangeBase
{
public:
	CMSD_EXPORT CPropertyCardinality(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CPropertyCardinality(CPropertyCardinality const& init);
	void operator=(CPropertyCardinality const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CPropertyCardinality); }
	MemberElement<CMinimumType, _altova_mi_altova_CPropertyCardinality_altova_Minimum> Minimum;
	struct Minimum { typedef Iterator<CMinimumType> iterator; };
	MemberElement<CMaximumType, _altova_mi_altova_CPropertyCardinality_altova_Maximum> Maximum;
	struct Maximum { typedef Iterator<CMaximumType> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPropertyCardinality
