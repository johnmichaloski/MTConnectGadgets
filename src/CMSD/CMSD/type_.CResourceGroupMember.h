#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CResourceGroupMember
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CResourceGroupMember

#include "type_.CResourceReference.h"


namespace CMSD
{

class CResourceGroupMember : public ::CMSD::CResourceReference
{
public:
	CMSD_EXPORT CResourceGroupMember(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CResourceGroupMember(CResourceGroupMember const& init);
	void operator=(CResourceGroupMember const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CResourceGroupMember); }
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CResourceGroupMember
