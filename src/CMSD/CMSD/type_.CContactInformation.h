#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CContactInformation
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CContactInformation

#include "type_.CCommunicationMethodGroup.h"


namespace CMSD
{

class CContactInformation : public ::CMSD::CCommunicationMethodGroup
{
public:
	CMSD_EXPORT CContactInformation(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CContactInformation(CContactInformation const& init);
	void operator=(CContactInformation const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CContactInformation); }
	MemberElement<CContactParty, _altova_mi_altova_CContactInformation_altova_ContactParty> ContactParty;
	struct ContactParty { typedef Iterator<CContactParty> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CContactInformation
