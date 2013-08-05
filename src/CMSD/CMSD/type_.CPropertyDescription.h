#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPropertyDescription
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPropertyDescription

#include "type_.CNotifyPropertyChangeBase.h"


namespace CMSD
{

class CPropertyDescription : public ::CMSD::CNotifyPropertyChangeBase
{
public:
	CMSD_EXPORT CPropertyDescription(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CPropertyDescription(CPropertyDescription const& init);
	void operator=(CPropertyDescription const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CPropertyDescription); }
	MemberElement<xs::CstringType, _altova_mi_altova_CPropertyDescription_altova_Identifier> Identifier;
	struct Identifier { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CPropertyDescription_altova_Name> Name;
	struct Name { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CPropertyDescription_altova_Description> Description;
	struct Description { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<CPropertyExtensibleEntityType, _altova_mi_altova_CPropertyDescription_altova_ParentEntityName> ParentEntityName;
	struct ParentEntityName { typedef Iterator<CPropertyExtensibleEntityType> iterator; };
	MemberElement<CUnitTypeNameType, _altova_mi_altova_CPropertyDescription_altova_UnitType> UnitType;
	struct UnitType { typedef Iterator<CUnitTypeNameType> iterator; };
	MemberElement<CPropertyCardinality, _altova_mi_altova_CPropertyDescription_altova_PropertyCardinality> PropertyCardinality;
	struct PropertyCardinality { typedef Iterator<CPropertyCardinality> iterator; };
	MemberElement<CPropertyDataTypeDescription, _altova_mi_altova_CPropertyDescription_altova_PropertyDataTypeDescription> PropertyDataTypeDescription;
	struct PropertyDataTypeDescription { typedef Iterator<CPropertyDataTypeDescription> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPropertyDescription
