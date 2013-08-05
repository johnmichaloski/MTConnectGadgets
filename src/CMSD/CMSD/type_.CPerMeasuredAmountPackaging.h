#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPerMeasuredAmountPackaging
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPerMeasuredAmountPackaging

#include "type_.CNotifyPropertyChangeBase.h"


namespace CMSD
{

class CPerMeasuredAmountPackaging : public ::CMSD::CNotifyPropertyChangeBase
{
public:
	CMSD_EXPORT CPerMeasuredAmountPackaging(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CPerMeasuredAmountPackaging(CPerMeasuredAmountPackaging const& init);
	void operator=(CPerMeasuredAmountPackaging const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CPerMeasuredAmountPackaging); }
	MemberElement<CMeasuredAmountType, _altova_mi_altova_CPerMeasuredAmountPackaging_altova_MeasuredAmount> MeasuredAmount;
	struct MeasuredAmount { typedef Iterator<CMeasuredAmountType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CPerMeasuredAmountPackaging_altova_PackageUnitOfMeasure> PackageUnitOfMeasure;
	struct PackageUnitOfMeasure { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<CCurrencyType, _altova_mi_altova_CPerMeasuredAmountPackaging_altova_PricePerUnit> PricePerUnit;
	struct PricePerUnit { typedef Iterator<CCurrencyType> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPerMeasuredAmountPackaging
