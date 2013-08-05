#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CVolumeType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CVolumeType

#include "type_.CNotifyPropertyChangeBase.h"


namespace CMSD
{

class CVolumeType : public ::CMSD::CNotifyPropertyChangeBase
{
public:
	CMSD_EXPORT CVolumeType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CVolumeType(CVolumeType const& init);
	void operator=(CVolumeType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CVolumeType); }
	MemberElement<CVolumeUnitType, _altova_mi_altova_CVolumeType_altova_Unit> Unit;
	struct Unit { typedef Iterator<CVolumeUnitType> iterator; };
	MemberElement<CValueType11, _altova_mi_altova_CVolumeType_altova_Value2> Value2;
	struct Value2 { typedef Iterator<CValueType11> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CVolumeType
