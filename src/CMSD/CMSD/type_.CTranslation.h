#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CTranslation
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CTranslation

#include "type_.CTransformationOperation.h"


namespace CMSD
{

class CTranslation : public ::CMSD::CTransformationOperation
{
public:
	CMSD_EXPORT CTranslation(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CTranslation(CTranslation const& init);
	void operator=(CTranslation const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CTranslation); }
	MemberElement<CXOffsetType, _altova_mi_altova_CTranslation_altova_XOffset> XOffset;
	struct XOffset { typedef Iterator<CXOffsetType> iterator; };
	MemberElement<CYOffsetType, _altova_mi_altova_CTranslation_altova_YOffset> YOffset;
	struct YOffset { typedef Iterator<CYOffsetType> iterator; };
	MemberElement<CZOffsetType, _altova_mi_altova_CTranslation_altova_ZOffset> ZOffset;
	struct ZOffset { typedef Iterator<CZOffsetType> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CTranslation
