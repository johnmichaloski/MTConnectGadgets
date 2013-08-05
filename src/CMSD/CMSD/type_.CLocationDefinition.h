#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CLocationDefinition
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CLocationDefinition

#include "type_.CNotifyPropertyChangeBase.h"


namespace CMSD
{

class CLocationDefinition : public ::CMSD::CNotifyPropertyChangeBase
{
public:
	CMSD_EXPORT CLocationDefinition(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CLocationDefinition(CLocationDefinition const& init);
	void operator=(CLocationDefinition const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CLocationDefinition); }
	MemberElement<xs::CstringType, _altova_mi_altova_CLocationDefinition_altova_FacilityLocation> FacilityLocation;
	struct FacilityLocation { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CLocationDefinition_altova_WithinFacilityLocation> WithinFacilityLocation;
	struct WithinFacilityLocation { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<CResourceReference, _altova_mi_altova_CLocationDefinition_altova_ResourceLocation> ResourceLocation;
	struct ResourceLocation { typedef Iterator<CResourceReference> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CLocationDefinition
