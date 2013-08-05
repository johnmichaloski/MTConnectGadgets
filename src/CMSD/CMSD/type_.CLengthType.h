#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CLengthType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CLengthType

#include "type_.CNotifyPropertyChangeBase.h"


namespace CMSD
{

class CLengthType : public ::CMSD::CNotifyPropertyChangeBase
{
public:
	CMSD_EXPORT CLengthType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CLengthType(CLengthType const& init);
	void operator=(CLengthType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CLengthType); }
	MemberElement<CLengthUnitType, _altova_mi_altova_CLengthType_altova_Unit> Unit;
	struct Unit { typedef Iterator<CLengthUnitType> iterator; };
	MemberElement<CValueType6, _altova_mi_altova_CLengthType_altova_Value2> Value2;
	struct Value2 { typedef Iterator<CValueType6> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CLengthType
