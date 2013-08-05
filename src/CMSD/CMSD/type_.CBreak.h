#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CBreak
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CBreak

#include "type_.CNotifyPropertyChangeBase.h"


namespace CMSD
{

class CBreak : public ::CMSD::CNotifyPropertyChangeBase
{
public:
	CMSD_EXPORT CBreak(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CBreak(CBreak const& init);
	void operator=(CBreak const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CBreak); }
	MemberElement<xs::CstringType, _altova_mi_altova_CBreak_altova_Description> Description;
	struct Description { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<CStartTimeType, _altova_mi_altova_CBreak_altova_StartTime> StartTime;
	struct StartTime { typedef Iterator<CStartTimeType> iterator; };
	MemberElement<CElapsedTimeType, _altova_mi_altova_CBreak_altova_Duration> Duration;
	struct Duration { typedef Iterator<CElapsedTimeType> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CBreak
