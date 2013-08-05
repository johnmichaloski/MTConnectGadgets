#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_COrderLinePartDescription
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_COrderLinePartDescription

#include "type_.CNotifyPropertyChangeBase.h"


namespace CMSD
{

class COrderLinePartDescription : public ::CMSD::CNotifyPropertyChangeBase
{
public:
	CMSD_EXPORT COrderLinePartDescription(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT COrderLinePartDescription(COrderLinePartDescription const& init);
	void operator=(COrderLinePartDescription const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_COrderLinePartDescription); }
	MemberElement<CPartTypeReference, _altova_mi_altova_COrderLinePartDescription_altova_PartType> PartType;
	struct PartType { typedef Iterator<CPartTypeReference> iterator; };
	MemberElement<CItemPackaging, _altova_mi_altova_COrderLinePartDescription_altova_Packaging> Packaging;
	struct Packaging { typedef Iterator<CItemPackaging> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_COrderLinePartDescription_altova_PartDetails> PartDetails;
	struct PartDetails { typedef Iterator<xs::CstringType> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_COrderLinePartDescription
