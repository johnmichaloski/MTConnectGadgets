#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CResourcesRequired
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CResourcesRequired

#include "type_.CNotifyPropertyChangeBase.h"


namespace CMSD
{

class CResourcesRequired : public ::CMSD::CNotifyPropertyChangeBase
{
public:
	CMSD_EXPORT CResourcesRequired(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CResourcesRequired(CResourcesRequired const& init);
	void operator=(CResourcesRequired const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CResourcesRequired); }
	MemberElement<xs::CstringType, _altova_mi_altova_CResourcesRequired_altova_Description> Description;
	struct Description { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<CResourceClassReference, _altova_mi_altova_CResourcesRequired_altova_ResourceClass> ResourceClass;
	struct ResourceClass { typedef Iterator<CResourceClassReference> iterator; };
	MemberElement<CMinimumNumberType, _altova_mi_altova_CResourcesRequired_altova_MinimumNumber> MinimumNumber;
	struct MinimumNumber { typedef Iterator<CMinimumNumberType> iterator; };
	MemberElement<CMaximumNumberType, _altova_mi_altova_CResourcesRequired_altova_MaximumNumber> MaximumNumber;
	struct MaximumNumber { typedef Iterator<CMaximumNumberType> iterator; };
	MemberElement<CResourceReference, _altova_mi_altova_CResourcesRequired_altova_Resource> Resource;
	struct Resource { typedef Iterator<CResourceReference> iterator; };
	MemberElement<CSetupDefinitionReference, _altova_mi_altova_CResourcesRequired_altova_AllowableSetup> AllowableSetup;
	struct AllowableSetup { typedef Iterator<CSetupDefinitionReference> iterator; };
	MemberElement<CSkillReference, _altova_mi_altova_CResourcesRequired_altova_RequiredEmployeeSkill> RequiredEmployeeSkill;
	struct RequiredEmployeeSkill { typedef Iterator<CSkillReference> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CResourcesRequired
