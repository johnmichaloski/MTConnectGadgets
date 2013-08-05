#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CReferenceMaterial
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CReferenceMaterial

#include "type_.CUniqueEntity.h"


namespace CMSD
{

class CReferenceMaterial : public ::CMSD::CUniqueEntity
{
public:
	CMSD_EXPORT CReferenceMaterial(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CReferenceMaterial(CReferenceMaterial const& init);
	void operator=(CReferenceMaterial const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CReferenceMaterial); }
	MemberElement<xs::CstringType, _altova_mi_altova_CReferenceMaterial_altova_FileName> FileName;
	struct FileName { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<COnlineLocationType, _altova_mi_altova_CReferenceMaterial_altova_OnlineLocation> OnlineLocation;
	struct OnlineLocation { typedef Iterator<COnlineLocationType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CReferenceMaterial_altova_ISBN> ISBN;
	struct ISBN { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CReferenceMaterial_altova_DigitalFormat> DigitalFormat;
	struct DigitalFormat { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CReferenceMaterial_altova_PermanentStorageMedium> PermanentStorageMedium;
	struct PermanentStorageMedium { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CReferenceMaterial_altova_PhysicalLocation> PhysicalLocation;
	struct PhysicalLocation { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<CRequiredApplication, _altova_mi_altova_CReferenceMaterial_altova_RequiredApplication> RequiredApplication;
	struct RequiredApplication { typedef Iterator<CRequiredApplication> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CReferenceMaterial
