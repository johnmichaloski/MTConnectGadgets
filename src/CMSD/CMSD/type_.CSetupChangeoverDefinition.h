#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CSetupChangeoverDefinition
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CSetupChangeoverDefinition

#include "type_.CUniqueEntity.h"


namespace CMSD
{

class CSetupChangeoverDefinition : public ::CMSD::CUniqueEntity
{
public:
	CMSD_EXPORT CSetupChangeoverDefinition(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CSetupChangeoverDefinition(CSetupChangeoverDefinition const& init);
	void operator=(CSetupChangeoverDefinition const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CSetupChangeoverDefinition); }
	MemberElement<CSetupDefinitionReference, _altova_mi_altova_CSetupChangeoverDefinition_altova_CurrentSetup> CurrentSetup;
	struct CurrentSetup { typedef Iterator<CSetupDefinitionReference> iterator; };
	MemberElement<CNewSetup, _altova_mi_altova_CSetupChangeoverDefinition_altova_NewSetup> NewSetup;
	struct NewSetup { typedef Iterator<CNewSetup> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CSetupChangeoverDefinition
