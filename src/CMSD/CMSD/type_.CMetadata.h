#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CMetadata
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CMetadata

#include "type_.CNotifyPropertyChangeBase.h"


namespace CMSD
{

class CMetadata : public ::CMSD::CNotifyPropertyChangeBase
{
public:
	CMSD_EXPORT CMetadata(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CMetadata(CMetadata const& init);
	void operator=(CMetadata const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CMetadata); }
	MemberElement<CPropertyDescription, _altova_mi_altova_CMetadata_altova_PropertyDescription> PropertyDescription;
	struct PropertyDescription { typedef Iterator<CPropertyDescription> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CMetadata
