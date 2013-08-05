#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CSkillReference
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CSkillReference

#include "type_.CAbstractEntityReference.h"


namespace CMSD
{

class CSkillReference : public ::CMSD::CAbstractEntityReference
{
public:
	CMSD_EXPORT CSkillReference(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CSkillReference(CSkillReference const& init);
	void operator=(CSkillReference const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CSkillReference); }
	MemberElement<xs::CstringType, _altova_mi_altova_CSkillReference_altova_SkillDefinitionIdentifier> SkillDefinitionIdentifier;
	struct SkillDefinitionIdentifier { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CSkillReference_altova_SkillLevelIdentifier> SkillLevelIdentifier;
	struct SkillLevelIdentifier { typedef Iterator<xs::CstringType> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CSkillReference
