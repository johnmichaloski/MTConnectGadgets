#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CQuantityType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CQuantityType

#include "type_.CNotifyPropertyChangeBase.h"


namespace CMSD
{

class CQuantityType : public ::CMSD::CNotifyPropertyChangeBase
{
public:
	CMSD_EXPORT CQuantityType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CQuantityType(CQuantityType const& init);
	void operator=(CQuantityType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CQuantityType); }
	MemberElement<xs::CstringType, _altova_mi_altova_CQuantityType_altova_UnitDescription> UnitDescription;
	struct UnitDescription { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CQuantityType_altova_UnitName> UnitName;
	struct UnitName { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<CValueType8, _altova_mi_altova_CQuantityType_altova_Value2> Value2;
	struct Value2 { typedef Iterator<CValueType8> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CQuantityType
