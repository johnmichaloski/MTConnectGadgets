#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CItemPackaging
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CItemPackaging

#include "type_.CNotifyPropertyChangeBase.h"


namespace CMSD
{

class CItemPackaging : public ::CMSD::CNotifyPropertyChangeBase
{
public:
	CMSD_EXPORT CItemPackaging(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CItemPackaging(CItemPackaging const& init);
	void operator=(CItemPackaging const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CItemPackaging); }
	MemberElement<xs::CstringType, _altova_mi_altova_CItemPackaging_altova_PackageName> PackageName;
	struct PackageName { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CItemPackaging_altova_PackageDescription> PackageDescription;
	struct PackageDescription { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<CPerPiecePackaging, _altova_mi_altova_CItemPackaging_altova_PerPiecePackaging> PerPiecePackaging;
	struct PerPiecePackaging { typedef Iterator<CPerPiecePackaging> iterator; };
	MemberElement<CPerMeasuredAmountPackaging, _altova_mi_altova_CItemPackaging_altova_PerMeasuredAmountPackaging> PerMeasuredAmountPackaging;
	struct PerMeasuredAmountPackaging { typedef Iterator<CPerMeasuredAmountPackaging> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CItemPackaging
