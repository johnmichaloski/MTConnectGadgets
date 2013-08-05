#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_COrderLine
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_COrderLine

#include "type_.CLimitedUniqueEntity.h"


namespace CMSD
{

class COrderLine : public ::CMSD::CLimitedUniqueEntity
{
public:
	CMSD_EXPORT COrderLine(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT COrderLine(COrderLine const& init);
	void operator=(COrderLine const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_COrderLine); }
	MemberElement<CUpdateTimeType4, _altova_mi_altova_COrderLine_altova_UpdateTime> UpdateTime;
	struct UpdateTime { typedef Iterator<CUpdateTimeType4> iterator; };
	MemberElement<COrderStatusType, _altova_mi_altova_COrderLine_altova_Status> Status;
	struct Status { typedef Iterator<COrderStatusType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_COrderLine_altova_ItemDescription> ItemDescription;
	struct ItemDescription { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<CItemQuantityType, _altova_mi_altova_COrderLine_altova_ItemQuantity> ItemQuantity;
	struct ItemQuantity { typedef Iterator<CItemQuantityType> iterator; };
	MemberElement<CCurrencyType, _altova_mi_altova_COrderLine_altova_ItemPrice> ItemPrice;
	struct ItemPrice { typedef Iterator<CCurrencyType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_COrderLine_altova_Priority> Priority;
	struct Priority { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<COrderLinePartDescription, _altova_mi_altova_COrderLine_altova_PartDescription> PartDescription;
	struct PartDescription { typedef Iterator<COrderLinePartDescription> iterator; };
	MemberElement<COrderLineServiceDescription, _altova_mi_altova_COrderLine_altova_ServiceDescription> ServiceDescription;
	struct ServiceDescription { typedef Iterator<COrderLineServiceDescription> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_COrderLine
