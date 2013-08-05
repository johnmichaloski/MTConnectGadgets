#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CReferencingEntity
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CReferencingEntity

#include "type_.CEntity.h"


namespace CMSD
{

class CReferencingEntity : public ::CMSD::CEntity
{
public:
	CMSD_EXPORT CReferencingEntity(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CReferencingEntity(CReferencingEntity const& init);
	void operator=(CReferencingEntity const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CReferencingEntity); }
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CReferencingEntity
