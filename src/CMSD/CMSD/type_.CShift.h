#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CShift
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CShift

#include "type_.CLimitedUniqueEntity.h"


namespace CMSD
{

class CShift : public ::CMSD::CLimitedUniqueEntity
{
public:
	CMSD_EXPORT CShift(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CShift(CShift const& init);
	void operator=(CShift const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CShift); }
	MemberElement<CStartTimeType5, _altova_mi_altova_CShift_altova_StartTime> StartTime;
	struct StartTime { typedef Iterator<CStartTimeType5> iterator; };
	MemberElement<CElapsedTimeType, _altova_mi_altova_CShift_altova_Duration> Duration;
	struct Duration { typedef Iterator<CElapsedTimeType> iterator; };
	MemberElement<CDayType, _altova_mi_altova_CShift_altova_ApplicableDay> ApplicableDay;
	struct ApplicableDay { typedef Iterator<CDayType> iterator; };
	MemberElement<CBreak, _altova_mi_altova_CShift_altova_Break2> Break2;
	struct Break2 { typedef Iterator<CBreak> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CShift
