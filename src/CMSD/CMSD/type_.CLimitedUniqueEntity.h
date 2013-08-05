#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CLimitedUniqueEntity
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CLimitedUniqueEntity

#include "type_.CIdentifiableEntity.h"


namespace CMSD
{

class CLimitedUniqueEntity : public ::CMSD::CIdentifiableEntity
{
public:
	CMSD_EXPORT CLimitedUniqueEntity(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CLimitedUniqueEntity(CLimitedUniqueEntity const& init);
	void operator=(CLimitedUniqueEntity const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CLimitedUniqueEntity); }
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CLimitedUniqueEntity
