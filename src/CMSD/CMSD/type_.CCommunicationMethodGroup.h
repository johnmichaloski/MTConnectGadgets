#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCommunicationMethodGroup
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCommunicationMethodGroup

#include "type_.CNotifyPropertyChangeBase.h"


namespace CMSD
{

class CCommunicationMethodGroup : public ::CMSD::CNotifyPropertyChangeBase
{
public:
	CMSD_EXPORT CCommunicationMethodGroup(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CCommunicationMethodGroup(CCommunicationMethodGroup const& init);
	void operator=(CCommunicationMethodGroup const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CCommunicationMethodGroup); }
	MemberElement<CAddress, _altova_mi_altova_CCommunicationMethodGroup_altova_Address> Address;
	struct Address { typedef Iterator<CAddress> iterator; };
	MemberElement<CPhone, _altova_mi_altova_CCommunicationMethodGroup_altova_Phone> Phone;
	struct Phone { typedef Iterator<CPhone> iterator; };
	MemberElement<CEmail, _altova_mi_altova_CCommunicationMethodGroup_altova_Email> Email;
	struct Email { typedef Iterator<CEmail> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCommunicationMethodGroup
