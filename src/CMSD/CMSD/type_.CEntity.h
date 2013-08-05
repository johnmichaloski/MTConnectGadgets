#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CEntity
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CEntity

#include "type_.CNotifyPropertyChangeBase.h"


namespace CMSD
{

class CEntity : public ::CMSD::CNotifyPropertyChangeBase
{
public:
	CMSD_EXPORT CEntity(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CEntity(CEntity const& init);
	void operator=(CEntity const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CEntity); }
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CEntity
