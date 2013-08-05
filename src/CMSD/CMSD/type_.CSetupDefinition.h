#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CSetupDefinition
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CSetupDefinition

#include "type_.CUniqueEntity.h"


namespace CMSD
{

class CSetupDefinition : public ::CMSD::CUniqueEntity
{
public:
	CMSD_EXPORT CSetupDefinition(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CSetupDefinition(CSetupDefinition const& init);
	void operator=(CSetupDefinition const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CSetupDefinition); }
	MemberElement<CResourceReference, _altova_mi_altova_CSetupDefinition_altova_SetupResource> SetupResource;
	struct SetupResource { typedef Iterator<CResourceReference> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CSetupDefinition_altova_Name> Name;
	struct Name { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<CResourceReference, _altova_mi_altova_CSetupDefinition_altova_SetupComponent> SetupComponent;
	struct SetupComponent { typedef Iterator<CResourceReference> iterator; };
	MemberElement<CSetupDefinitionReference, _altova_mi_altova_CSetupDefinition_altova_ChildSetup> ChildSetup;
	struct ChildSetup { typedef Iterator<CSetupDefinitionReference> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CSetupDefinition
