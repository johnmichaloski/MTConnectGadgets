#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPartGroup
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPartGroup

#include "type_.CNotifyPropertyChangeBase.h"


namespace CMSD
{

class CPartGroup : public ::CMSD::CNotifyPropertyChangeBase
{
public:
	CMSD_EXPORT CPartGroup(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CPartGroup(CPartGroup const& init);
	void operator=(CPartGroup const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CPartGroup); }
	MemberElement<xs::CstringType, _altova_mi_altova_CPartGroup_altova_Description> Description;
	struct Description { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<CPartTypeReference, _altova_mi_altova_CPartGroup_altova_PartType> PartType;
	struct PartType { typedef Iterator<CPartTypeReference> iterator; };
	MemberElement<CPartQuantityType, _altova_mi_altova_CPartGroup_altova_PartQuantity> PartQuantity;
	struct PartQuantity { typedef Iterator<CPartQuantityType> iterator; };
	MemberElement<CPartReference, _altova_mi_altova_CPartGroup_altova_PartInstance> PartInstance;
	struct PartInstance { typedef Iterator<CPartReference> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPartGroup
