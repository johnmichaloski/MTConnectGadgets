#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CTransformationOperation
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CTransformationOperation

#include "type_.CNotifyPropertyChangeBase.h"


namespace CMSD
{

class CTransformationOperation : public ::CMSD::CNotifyPropertyChangeBase
{
public:
	CMSD_EXPORT CTransformationOperation(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CTransformationOperation(CTransformationOperation const& init);
	void operator=(CTransformationOperation const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CTransformationOperation); }
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CTransformationOperation
