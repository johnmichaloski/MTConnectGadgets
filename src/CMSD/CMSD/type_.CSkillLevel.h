#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CSkillLevel
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CSkillLevel

#include "type_.CLimitedUniqueEntity.h"


namespace CMSD
{

class CSkillLevel : public ::CMSD::CLimitedUniqueEntity
{
public:
	CMSD_EXPORT CSkillLevel(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CSkillLevel(CSkillLevel const& init);
	void operator=(CSkillLevel const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CSkillLevel); }
	MemberElement<xs::CstringType, _altova_mi_altova_CSkillLevel_altova_Name> Name;
	struct Name { typedef Iterator<xs::CstringType> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CSkillLevel
