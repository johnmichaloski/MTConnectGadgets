#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_COrder
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_COrder

#include "type_.CUniqueEntity.h"


namespace CMSD
{

class COrder : public ::CMSD::CUniqueEntity
{
public:
	CMSD_EXPORT COrder(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT COrder(COrder const& init);
	void operator=(COrder const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_COrder); }
	MemberElement<COrderStatusType, _altova_mi_altova_COrder_altova_Status> Status;
	struct Status { typedef Iterator<COrderStatusType> iterator; };
	MemberElement<CUpdateTimeType3, _altova_mi_altova_COrder_altova_UpdateTime> UpdateTime;
	struct UpdateTime { typedef Iterator<CUpdateTimeType3> iterator; };
	MemberElement<CContactInformation, _altova_mi_altova_COrder_altova_CustomerParty> CustomerParty;
	struct CustomerParty { typedef Iterator<CContactInformation> iterator; };
	MemberElement<CContactInformation, _altova_mi_altova_COrder_altova_SupplierParty> SupplierParty;
	struct SupplierParty { typedef Iterator<CContactInformation> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_COrder_altova_SpecialInstruction> SpecialInstruction;
	struct SpecialInstruction { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<CCurrencyType, _altova_mi_altova_COrder_altova_TotalPrice> TotalPrice;
	struct TotalPrice { typedef Iterator<CCurrencyType> iterator; };
	MemberElement<CDueDateType2, _altova_mi_altova_COrder_altova_DueDate> DueDate;
	struct DueDate { typedef Iterator<CDueDateType2> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_COrder_altova_Priority> Priority;
	struct Priority { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<COrderLine, _altova_mi_altova_COrder_altova_OrderLine> OrderLine;
	struct OrderLine { typedef Iterator<COrderLine> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_COrder
