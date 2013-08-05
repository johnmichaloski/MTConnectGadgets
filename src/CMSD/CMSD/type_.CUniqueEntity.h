#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CUniqueEntity
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CUniqueEntity

#include "type_.CIdentifiableEntity.h"


namespace CMSD
{

class CUniqueEntity : public ::CMSD::CIdentifiableEntity
{
public:
	CMSD_EXPORT CUniqueEntity(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CUniqueEntity(CUniqueEntity const& init);
	void operator=(CUniqueEntity const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CUniqueEntity); }
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CUniqueEntity
