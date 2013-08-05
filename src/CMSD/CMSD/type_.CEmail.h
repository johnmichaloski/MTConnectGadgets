#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CEmail
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CEmail

#include "type_.CCommunicationMethod.h"


namespace CMSD
{

class CEmail : public ::CMSD::CCommunicationMethod
{
public:
	CMSD_EXPORT CEmail(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CEmail(CEmail const& init);
	void operator=(CEmail const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CEmail); }
	MemberElement<CAddressType, _altova_mi_altova_CEmail_altova_Address> Address;
	struct Address { typedef Iterator<CAddressType> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CEmail
