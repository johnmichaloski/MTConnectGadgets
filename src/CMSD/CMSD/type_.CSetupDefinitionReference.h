#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CSetupDefinitionReference
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CSetupDefinitionReference

#include "type_.CAbstractEntityReference.h"


namespace CMSD
{

class CSetupDefinitionReference : public ::CMSD::CAbstractEntityReference
{
public:
	CMSD_EXPORT CSetupDefinitionReference(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CSetupDefinitionReference(CSetupDefinitionReference const& init);
	void operator=(CSetupDefinitionReference const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CSetupDefinitionReference); }
	MemberElement<xs::CstringType, _altova_mi_altova_CSetupDefinitionReference_altova_SetupDefinitionIdentifier> SetupDefinitionIdentifier;
	struct SetupDefinitionIdentifier { typedef Iterator<xs::CstringType> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CSetupDefinitionReference
