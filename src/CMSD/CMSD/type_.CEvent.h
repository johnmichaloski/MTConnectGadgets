#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CEvent
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CEvent

#include "type_.CNotifyPropertyChangeBase.h"


namespace CMSD
{

class CEvent : public ::CMSD::CNotifyPropertyChangeBase
{
public:
	CMSD_EXPORT CEvent(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CEvent(CEvent const& init);
	void operator=(CEvent const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CEvent); }
	MemberElement<xs::CstringType, _altova_mi_altova_CEvent_altova_SequenceNumber> SequenceNumber;
	struct SequenceNumber { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CEvent_altova_Name> Name;
	struct Name { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CEvent_altova_Description> Description;
	struct Description { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<CTimestampType2, _altova_mi_altova_CEvent_altova_Timestamp> Timestamp;
	struct Timestamp { typedef Iterator<CTimestampType2> iterator; };
	MemberElement<CProperty, _altova_mi_altova_CEvent_altova_Property> Property;
	struct Property { typedef Iterator<CProperty> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CEvent
