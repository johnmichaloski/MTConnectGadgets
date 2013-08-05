#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CProcessGroup
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CProcessGroup

#include "type_.CNotifyPropertyChangeBase.h"


namespace CMSD
{

class CProcessGroup : public ::CMSD::CNotifyPropertyChangeBase
{
public:
	CMSD_EXPORT CProcessGroup(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CProcessGroup(CProcessGroup const& init);
	void operator=(CProcessGroup const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CProcessGroup); }
	MemberElement<CProcessGroupTypeType, _altova_mi_altova_CProcessGroup_altova_Type> Type;
	struct Type { typedef Iterator<CProcessGroupTypeType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CProcessGroup_altova_DecisionText> DecisionText;
	struct DecisionText { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<CProcessReference, _altova_mi_altova_CProcessGroup_altova_Process> Process;
	struct Process { typedef Iterator<CProcessReference> iterator; };
	MemberElement<CProcessConstraint, _altova_mi_altova_CProcessGroup_altova_ProcessConstraint> ProcessConstraint;
	struct ProcessConstraint { typedef Iterator<CProcessConstraint> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CProcessGroup
