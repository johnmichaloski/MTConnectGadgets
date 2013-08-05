#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPrecedenceConstraint
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPrecedenceConstraint

#include "type_.CNotifyPropertyChangeBase.h"


namespace CMSD
{

class CPrecedenceConstraint : public ::CMSD::CNotifyPropertyChangeBase
{
public:
	CMSD_EXPORT CPrecedenceConstraint(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CPrecedenceConstraint(CPrecedenceConstraint const& init);
	void operator=(CPrecedenceConstraint const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CPrecedenceConstraint); }
	MemberElement<xs::CstringType, _altova_mi_altova_CPrecedenceConstraint_altova_Description> Description;
	struct Description { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<CPrecedenceRelationshipType, _altova_mi_altova_CPrecedenceConstraint_altova_PrecedenceRelationship> PrecedenceRelationship;
	struct PrecedenceRelationship { typedef Iterator<CPrecedenceRelationshipType> iterator; };
	MemberElement<CElapsedTimeType, _altova_mi_altova_CPrecedenceConstraint_altova_LagDuration> LagDuration;
	struct LagDuration { typedef Iterator<CElapsedTimeType> iterator; };
	MemberElement<CLagPercentageType, _altova_mi_altova_CPrecedenceConstraint_altova_LagPercentage> LagPercentage;
	struct LagPercentage { typedef Iterator<CLagPercentageType> iterator; };
	MemberElement<CLagPartsCompleteType, _altova_mi_altova_CPrecedenceConstraint_altova_LagPartsComplete> LagPartsComplete;
	struct LagPartsComplete { typedef Iterator<CLagPartsCompleteType> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPrecedenceConstraint
