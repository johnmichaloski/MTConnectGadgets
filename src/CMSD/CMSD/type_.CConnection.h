#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CConnection
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CConnection

#include "type_.CLimitedUniqueEntity.h"


namespace CMSD
{

class CConnection : public ::CMSD::CLimitedUniqueEntity
{
public:
	CMSD_EXPORT CConnection(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CConnection(CConnection const& init);
	void operator=(CConnection const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CConnection); }
	MemberElement<CResourceReference, _altova_mi_altova_CConnection_altova_FromResource> FromResource;
	struct FromResource { typedef Iterator<CResourceReference> iterator; };
	MemberElement<CResourceReference, _altova_mi_altova_CConnection_altova_ToResource> ToResource;
	struct ToResource { typedef Iterator<CResourceReference> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CConnection
