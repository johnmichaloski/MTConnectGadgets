#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPhone
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPhone

#include "type_.CCommunicationMethod.h"


namespace CMSD
{

class CPhone : public ::CMSD::CCommunicationMethod
{
public:
	CMSD_EXPORT CPhone(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CPhone(CPhone const& init);
	void operator=(CPhone const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CPhone); }
	MemberElement<xs::CstringType, _altova_mi_altova_CPhone_altova_Number> Number;
	struct Number { typedef Iterator<xs::CstringType> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPhone
