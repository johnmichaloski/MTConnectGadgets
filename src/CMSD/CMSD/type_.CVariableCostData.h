#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CVariableCostData
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CVariableCostData

#include "type_.CNotifyPropertyChangeBase.h"


namespace CMSD
{

class CVariableCostData : public ::CMSD::CNotifyPropertyChangeBase
{
public:
	CMSD_EXPORT CVariableCostData(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CVariableCostData(CVariableCostData const& init);
	void operator=(CVariableCostData const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CVariableCostData); }
	MemberElement<xs::CstringType, _altova_mi_altova_CVariableCostData_altova_CostUnit> CostUnit;
	struct CostUnit { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<CCostRatePerUnitType, _altova_mi_altova_CVariableCostData_altova_CostRatePerUnit> CostRatePerUnit;
	struct CostRatePerUnit { typedef Iterator<CCostRatePerUnitType> iterator; };
	MemberElement<CCostUnitQuantityType, _altova_mi_altova_CVariableCostData_altova_CostUnitQuantity> CostUnitQuantity;
	struct CostUnitQuantity { typedef Iterator<CCostUnitQuantityType> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CVariableCostData
