#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_COrderLineServiceDescription
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_COrderLineServiceDescription

#include "type_.CNotifyPropertyChangeBase.h"


namespace CMSD
{

class COrderLineServiceDescription : public ::CMSD::CNotifyPropertyChangeBase
{
public:
	CMSD_EXPORT COrderLineServiceDescription(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT COrderLineServiceDescription(COrderLineServiceDescription const& init);
	void operator=(COrderLineServiceDescription const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_COrderLineServiceDescription); }
	MemberElement<xs::CstringType, _altova_mi_altova_COrderLineServiceDescription_altova_ServiceIdentifier> ServiceIdentifier;
	struct ServiceIdentifier { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_COrderLineServiceDescription_altova_ServiceDetails> ServiceDetails;
	struct ServiceDetails { typedef Iterator<xs::CstringType> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_COrderLineServiceDescription
