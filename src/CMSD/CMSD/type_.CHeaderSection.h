#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CHeaderSection
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CHeaderSection

#include "type_.CNotifyPropertyChangeBase.h"


namespace CMSD
{

class CHeaderSection : public ::CMSD::CNotifyPropertyChangeBase
{
public:
	CMSD_EXPORT CHeaderSection(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CHeaderSection(CHeaderSection const& init);
	void operator=(CHeaderSection const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CHeaderSection); }
	MemberElement<xs::CstringType, _altova_mi_altova_CHeaderSection_altova_DocumentIdentifier> DocumentIdentifier;
	struct DocumentIdentifier { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CHeaderSection_altova_Description> Description;
	struct Description { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CHeaderSection_altova_Version> Version;
	struct Version { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<CCreationTimeType, _altova_mi_altova_CHeaderSection_altova_CreationTime> CreationTime;
	struct CreationTime { typedef Iterator<CCreationTimeType> iterator; };
	MemberElement<CMetadata, _altova_mi_altova_CHeaderSection_altova_Metadata> Metadata;
	struct Metadata { typedef Iterator<CMetadata> iterator; };
	MemberElement<CCMSDDocumentReference, _altova_mi_altova_CHeaderSection_altova_CMSDDocumentReference> CMSDDocumentReference;
	struct CMSDDocumentReference { typedef Iterator<CCMSDDocumentReference> iterator; };
	MemberElement<CUnitDefaults, _altova_mi_altova_CHeaderSection_altova_UnitDefaults> UnitDefaults;
	struct UnitDefaults { typedef Iterator<CUnitDefaults> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CHeaderSection
