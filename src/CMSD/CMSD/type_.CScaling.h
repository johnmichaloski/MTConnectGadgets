#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CScaling
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CScaling

#include "type_.CTransformationOperation.h"


namespace CMSD
{

class CScaling : public ::CMSD::CTransformationOperation
{
public:
	CMSD_EXPORT CScaling(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CScaling(CScaling const& init);
	void operator=(CScaling const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CScaling); }
	MemberElement<CXPercentType, _altova_mi_altova_CScaling_altova_XPercent> XPercent;
	struct XPercent { typedef Iterator<CXPercentType> iterator; };
	MemberElement<CYPercentType, _altova_mi_altova_CScaling_altova_YPercent> YPercent;
	struct YPercent { typedef Iterator<CYPercentType> iterator; };
	MemberElement<CZPercentType, _altova_mi_altova_CScaling_altova_ZPercent> ZPercent;
	struct ZPercent { typedef Iterator<CZPercentType> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CScaling
