#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CProcessPlanReference
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CProcessPlanReference

#include "type_.CAbstractEntityReference.h"


namespace CMSD
{

class CProcessPlanReference : public ::CMSD::CAbstractEntityReference
{
public:
	CMSD_EXPORT CProcessPlanReference(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CProcessPlanReference(CProcessPlanReference const& init);
	void operator=(CProcessPlanReference const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CProcessPlanReference); }
	MemberElement<xs::CstringType, _altova_mi_altova_CProcessPlanReference_altova_ProcessPlanIdentifier> ProcessPlanIdentifier;
	struct ProcessPlanIdentifier { typedef Iterator<xs::CstringType> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CProcessPlanReference
