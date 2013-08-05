#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CResource
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CResource

#include "type_.CUniqueEntity.h"


namespace CMSD
{

class CResource : public ::CMSD::CUniqueEntity
{
public:
	CMSD_EXPORT CResource(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CResource(CResource const& init);
	void operator=(CResource const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CResource); }
	MemberElement<CResourceTypeType, _altova_mi_altova_CResource_altova_ResourceType> ResourceType;
	struct ResourceType { typedef Iterator<CResourceTypeType> iterator; };
	MemberElement<CResourceClassReference, _altova_mi_altova_CResource_altova_ResourceClass> ResourceClass;
	struct ResourceClass { typedef Iterator<CResourceClassReference> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CResource_altova_Name> Name;
	struct Name { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<CResourceStatusType, _altova_mi_altova_CResource_altova_CurrentStatus> CurrentStatus;
	struct CurrentStatus { typedef Iterator<CResourceStatusType> iterator; };
	MemberElement<CSetupDefinitionReference, _altova_mi_altova_CResource_altova_CurrentSetup> CurrentSetup;
	struct CurrentSetup { typedef Iterator<CSetupDefinitionReference> iterator; };
	MemberElement<CCalendarReference, _altova_mi_altova_CResource_altova_ShiftAssignment> ShiftAssignment;
	struct ShiftAssignment { typedef Iterator<CCalendarReference> iterator; };
	MemberElement<CResourceReference, _altova_mi_altova_CResource_altova_AssociatedResource> AssociatedResource;
	struct AssociatedResource { typedef Iterator<CResourceReference> iterator; };
	MemberElement<CCurrencyType, _altova_mi_altova_CResource_altova_HourlyRate> HourlyRate;
	struct HourlyRate { typedef Iterator<CCurrencyType> iterator; };
	MemberElement<CSkillReference, _altova_mi_altova_CResource_altova_EmployeeSkill> EmployeeSkill;
	struct EmployeeSkill { typedef Iterator<CSkillReference> iterator; };
	MemberElement<CResourceGroupInformation, _altova_mi_altova_CResource_altova_GroupDefinition> GroupDefinition;
	struct GroupDefinition { typedef Iterator<CResourceGroupInformation> iterator; };
	MemberElement<CGrossDimensions, _altova_mi_altova_CResource_altova_Size> Size;
	struct Size { typedef Iterator<CGrossDimensions> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CResource
