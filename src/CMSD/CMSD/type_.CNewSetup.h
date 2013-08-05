#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CNewSetup
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CNewSetup

#include "type_.CSetupDefinitionReference.h"


namespace CMSD
{

class CNewSetup : public ::CMSD::CSetupDefinitionReference
{
public:
	CMSD_EXPORT CNewSetup(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CNewSetup(CNewSetup const& init);
	void operator=(CNewSetup const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CNewSetup); }
	MemberElement<CDuration, _altova_mi_altova_CNewSetup_altova_ChangeoverTime> ChangeoverTime;
	struct ChangeoverTime { typedef Iterator<CDuration> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CNewSetup
