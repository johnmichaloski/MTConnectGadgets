#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CJobReference
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CJobReference

#include "type_.CAbstractEntityReference.h"


namespace CMSD
{

class CJobReference : public ::CMSD::CAbstractEntityReference
{
public:
	CMSD_EXPORT CJobReference(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CJobReference(CJobReference const& init);
	void operator=(CJobReference const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CJobReference); }
	MemberElement<xs::CstringType, _altova_mi_altova_CJobReference_altova_JobIdentifier> JobIdentifier;
	struct JobIdentifier { typedef Iterator<xs::CstringType> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CJobReference
