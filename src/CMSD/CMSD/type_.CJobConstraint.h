#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CJobConstraint
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CJobConstraint

#include "type_.CPrecedenceConstraint.h"


namespace CMSD
{

class CJobConstraint : public ::CMSD::CPrecedenceConstraint
{
public:
	CMSD_EXPORT CJobConstraint(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CJobConstraint(CJobConstraint const& init);
	void operator=(CJobConstraint const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CJobConstraint); }
	MemberElement<CJobReference, _altova_mi_altova_CJobConstraint_altova_PredecessorJob> PredecessorJob;
	struct PredecessorJob { typedef Iterator<CJobReference> iterator; };
	MemberElement<CJobReference, _altova_mi_altova_CJobConstraint_altova_SuccessorJob> SuccessorJob;
	struct SuccessorJob { typedef Iterator<CJobReference> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CJobConstraint
