#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CContactParty
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CContactParty

#include "type_.CCommunicationMethodGroup.h"


namespace CMSD
{

class CContactParty : public ::CMSD::CCommunicationMethodGroup
{
public:
	CMSD_EXPORT CContactParty(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CContactParty(CContactParty const& init);
	void operator=(CContactParty const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CContactParty); }
	MemberElement<xs::CstringType, _altova_mi_altova_CContactParty_altova_PersonName> PersonName;
	struct PersonName { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CContactParty_altova_OrganizationName> OrganizationName;
	struct OrganizationName { typedef Iterator<xs::CstringType> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CContactParty
