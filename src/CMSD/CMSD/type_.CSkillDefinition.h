#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CSkillDefinition
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CSkillDefinition

#include "type_.CUniqueEntity.h"


namespace CMSD
{

class CSkillDefinition : public ::CMSD::CUniqueEntity
{
public:
	CMSD_EXPORT CSkillDefinition(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CSkillDefinition(CSkillDefinition const& init);
	void operator=(CSkillDefinition const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CSkillDefinition); }
	MemberElement<xs::CstringType, _altova_mi_altova_CSkillDefinition_altova_Name> Name;
	struct Name { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<CSkillLevel, _altova_mi_altova_CSkillDefinition_altova_SkillLevel> SkillLevel;
	struct SkillLevel { typedef Iterator<CSkillLevel> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CSkillDefinition
