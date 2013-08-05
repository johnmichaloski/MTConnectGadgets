#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CProcessReference
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CProcessReference

#include "type_.CAbstractEntityReference.h"


namespace CMSD
{

class CProcessReference : public ::CMSD::CAbstractEntityReference
{
public:
	CMSD_EXPORT CProcessReference(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CProcessReference(CProcessReference const& init);
	void operator=(CProcessReference const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CProcessReference); }
	MemberElement<xs::CstringType, _altova_mi_altova_CProcessReference_altova_ProcessPlanIdentifier> ProcessPlanIdentifier;
	struct ProcessPlanIdentifier { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CProcessReference_altova_ProcessIdentifier> ProcessIdentifier;
	struct ProcessIdentifier { typedef Iterator<xs::CstringType> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CProcessReference
