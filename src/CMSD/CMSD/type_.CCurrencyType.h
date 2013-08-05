#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCurrencyType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCurrencyType

#include "type_.CNotifyPropertyChangeBase.h"


namespace CMSD
{

class CCurrencyType : public ::CMSD::CNotifyPropertyChangeBase
{
public:
	CMSD_EXPORT CCurrencyType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CCurrencyType(CCurrencyType const& init);
	void operator=(CCurrencyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CCurrencyType); }
	MemberElement<xs::CstringType, _altova_mi_altova_CCurrencyType_altova_Unit> Unit;
	struct Unit { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<CValueType2, _altova_mi_altova_CCurrencyType_altova_Value2> Value2;
	struct Value2 { typedef Iterator<CValueType2> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCurrencyType
