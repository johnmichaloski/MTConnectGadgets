#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CProcessConstraint
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CProcessConstraint

#include "type_.CPrecedenceConstraint.h"


namespace CMSD
{

class CProcessConstraint : public ::CMSD::CPrecedenceConstraint
{
public:
	CMSD_EXPORT CProcessConstraint(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CProcessConstraint(CProcessConstraint const& init);
	void operator=(CProcessConstraint const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CProcessConstraint); }
	MemberElement<CProcessReference, _altova_mi_altova_CProcessConstraint_altova_PredecessorProcess> PredecessorProcess;
	struct PredecessorProcess { typedef Iterator<CProcessReference> iterator; };
	MemberElement<CProcessReference, _altova_mi_altova_CProcessConstraint_altova_SuccessorProcess> SuccessorProcess;
	struct SuccessorProcess { typedef Iterator<CProcessReference> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CProcessConstraint
