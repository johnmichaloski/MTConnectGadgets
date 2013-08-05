#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPerPiecePackaging
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPerPiecePackaging

#include "type_.CNotifyPropertyChangeBase.h"


namespace CMSD
{

class CPerPiecePackaging : public ::CMSD::CNotifyPropertyChangeBase
{
public:
	CMSD_EXPORT CPerPiecePackaging(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CPerPiecePackaging(CPerPiecePackaging const& init);
	void operator=(CPerPiecePackaging const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CPerPiecePackaging); }
	MemberElement<CPiecesPerPackageType, _altova_mi_altova_CPerPiecePackaging_altova_PiecesPerPackage> PiecesPerPackage;
	struct PiecesPerPackage { typedef Iterator<CPiecesPerPackageType> iterator; };
	MemberElement<CCurrencyType, _altova_mi_altova_CPerPiecePackaging_altova_PricePerPiece> PricePerPiece;
	struct PricePerPiece { typedef Iterator<CCurrencyType> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPerPiecePackaging
