#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPropertyDescriptionReference
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPropertyDescriptionReference

#include "type_.CAbstractEntityReference.h"


namespace CMSD
{

class CPropertyDescriptionReference : public ::CMSD::CAbstractEntityReference
{
public:
	CMSD_EXPORT CPropertyDescriptionReference(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CPropertyDescriptionReference(CPropertyDescriptionReference const& init);
	void operator=(CPropertyDescriptionReference const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CPropertyDescriptionReference); }
	MemberElement<xs::CstringType, _altova_mi_altova_CPropertyDescriptionReference_altova_PropertyDescriptionIdentifier> PropertyDescriptionIdentifier;
	struct PropertyDescriptionIdentifier { typedef Iterator<xs::CstringType> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPropertyDescriptionReference
