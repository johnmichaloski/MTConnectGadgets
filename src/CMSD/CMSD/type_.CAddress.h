#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CAddress
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CAddress

#include "type_.CCommunicationMethod.h"


namespace CMSD
{

class CAddress : public ::CMSD::CCommunicationMethod
{
public:
	CMSD_EXPORT CAddress(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CAddress(CAddress const& init);
	void operator=(CAddress const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CAddress); }
	MemberElement<xs::CstringType, _altova_mi_altova_CAddress_altova_OrganizationName> OrganizationName;
	struct OrganizationName { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CAddress_altova_Street> Street;
	struct Street { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CAddress_altova_PostOfficeBox> PostOfficeBox;
	struct PostOfficeBox { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CAddress_altova_AdditionalInformation> AdditionalInformation;
	struct AdditionalInformation { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CAddress_altova_City> City;
	struct City { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CAddress_altova_State> State;
	struct State { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CAddress_altova_Country> Country;
	struct Country { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CAddress_altova_PostalCode> PostalCode;
	struct PostalCode { typedef Iterator<xs::CstringType> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CAddress
