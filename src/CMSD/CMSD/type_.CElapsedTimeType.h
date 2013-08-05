#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CElapsedTimeType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CElapsedTimeType

#include "type_.CNotifyPropertyChangeBase.h"


namespace CMSD
{

class CElapsedTimeType : public ::CMSD::CNotifyPropertyChangeBase
{
public:
	CMSD_EXPORT CElapsedTimeType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CElapsedTimeType(CElapsedTimeType const& init);
	void operator=(CElapsedTimeType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CElapsedTimeType); }
	MemberElement<CTimeUnitType, _altova_mi_altova_CElapsedTimeType_altova_Unit> Unit;
	struct Unit { typedef Iterator<CTimeUnitType> iterator; };
	MemberElement<CValueType5, _altova_mi_altova_CElapsedTimeType_altova_Value2> Value2;
	struct Value2 { typedef Iterator<CValueType5> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CElapsedTimeType
