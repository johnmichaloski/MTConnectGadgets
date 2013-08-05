#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CSetupChangeoverReference
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CSetupChangeoverReference

#include "type_.CAbstractEntityReference.h"


namespace CMSD
{

class CSetupChangeoverReference : public ::CMSD::CAbstractEntityReference
{
public:
	CMSD_EXPORT CSetupChangeoverReference(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CSetupChangeoverReference(CSetupChangeoverReference const& init);
	void operator=(CSetupChangeoverReference const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CSetupChangeoverReference); }
	MemberElement<xs::CstringType, _altova_mi_altova_CSetupChangeoverReference_altova_SetupChangeoverIdentifier> SetupChangeoverIdentifier;
	struct SetupChangeoverIdentifier { typedef Iterator<xs::CstringType> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CSetupChangeoverReference
