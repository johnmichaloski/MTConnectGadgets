#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CResourceClass
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CResourceClass

#include "type_.CUniqueEntity.h"


namespace CMSD
{

class CResourceClass : public ::CMSD::CUniqueEntity
{
public:
	CMSD_EXPORT CResourceClass(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CResourceClass(CResourceClass const& init);
	void operator=(CResourceClass const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CResourceClass); }
	MemberElement<CResourceTypeType, _altova_mi_altova_CResourceClass_altova_ResourceType> ResourceType;
	struct ResourceType { typedef Iterator<CResourceTypeType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CResourceClass_altova_Name> Name;
	struct Name { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<CCurrencyType, _altova_mi_altova_CResourceClass_altova_HourlyRate> HourlyRate;
	struct HourlyRate { typedef Iterator<CCurrencyType> iterator; };
	MemberElement<CGrossDimensions, _altova_mi_altova_CResourceClass_altova_Size> Size;
	struct Size { typedef Iterator<CGrossDimensions> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CResourceClass
