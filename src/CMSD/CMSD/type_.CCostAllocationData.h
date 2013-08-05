#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCostAllocationData
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCostAllocationData

#include "type_.CNotifyPropertyChangeBase.h"


namespace CMSD
{

class CCostAllocationData : public ::CMSD::CNotifyPropertyChangeBase
{
public:
	CMSD_EXPORT CCostAllocationData(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CCostAllocationData(CCostAllocationData const& init);
	void operator=(CCostAllocationData const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CCostAllocationData); }
	MemberElement<CCostCategoryType, _altova_mi_altova_CCostAllocationData_altova_CostCategory> CostCategory;
	struct CostCategory { typedef Iterator<CCostCategoryType> iterator; };
	MemberElement<CCostTypeType, _altova_mi_altova_CCostAllocationData_altova_CostType> CostType;
	struct CostType { typedef Iterator<CCostTypeType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CCostAllocationData_altova_CostName> CostName;
	struct CostName { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CCostAllocationData_altova_CostDescription> CostDescription;
	struct CostDescription { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<CCurrencyType, _altova_mi_altova_CCostAllocationData_altova_TotalCost> TotalCost;
	struct TotalCost { typedef Iterator<CCurrencyType> iterator; };
	MemberElement<CProperty, _altova_mi_altova_CCostAllocationData_altova_Property> Property;
	struct Property { typedef Iterator<CProperty> iterator; };
	MemberElement<CVariableCostData, _altova_mi_altova_CCostAllocationData_altova_VariableCostData> VariableCostData;
	struct VariableCostData { typedef Iterator<CVariableCostData> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCostAllocationData
