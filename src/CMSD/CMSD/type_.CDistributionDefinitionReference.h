#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CDistributionDefinitionReference
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CDistributionDefinitionReference

#include "type_.CAbstractEntityReference.h"


namespace CMSD
{

class CDistributionDefinitionReference : public ::CMSD::CAbstractEntityReference
{
public:
	CMSD_EXPORT CDistributionDefinitionReference(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CDistributionDefinitionReference(CDistributionDefinitionReference const& init);
	void operator=(CDistributionDefinitionReference const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CDistributionDefinitionReference); }
	MemberElement<xs::CstringType, _altova_mi_altova_CDistributionDefinitionReference_altova_DistributionDefinitionIdentifier> DistributionDefinitionIdentifier;
	struct DistributionDefinitionIdentifier { typedef Iterator<xs::CstringType> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CDistributionDefinitionReference
