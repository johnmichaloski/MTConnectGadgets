#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_COrderInformationReference
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_COrderInformationReference

#include "type_.CAbstractEntityReference.h"


namespace CMSD
{

class COrderInformationReference : public ::CMSD::CAbstractEntityReference
{
public:
	CMSD_EXPORT COrderInformationReference(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT COrderInformationReference(COrderInformationReference const& init);
	void operator=(COrderInformationReference const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_COrderInformationReference); }
	MemberElement<xs::CstringType, _altova_mi_altova_COrderInformationReference_altova_OrderIdentifier> OrderIdentifier;
	struct OrderIdentifier { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_COrderInformationReference_altova_OrderLineIdentifier> OrderLineIdentifier;
	struct OrderLineIdentifier { typedef Iterator<xs::CstringType> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_COrderInformationReference
