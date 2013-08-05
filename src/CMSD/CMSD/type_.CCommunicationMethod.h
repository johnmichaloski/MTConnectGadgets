#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCommunicationMethod
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCommunicationMethod

#include "type_.CNotifyPropertyChangeBase.h"


namespace CMSD
{

class CCommunicationMethod : public ::CMSD::CNotifyPropertyChangeBase
{
public:
	CMSD_EXPORT CCommunicationMethod(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CCommunicationMethod(CCommunicationMethod const& init);
	void operator=(CCommunicationMethod const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CCommunicationMethod); }
	MemberElement<xs::CstringType, _altova_mi_altova_CCommunicationMethod_altova_Description> Description;
	struct Description { typedef Iterator<xs::CstringType> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCommunicationMethod
