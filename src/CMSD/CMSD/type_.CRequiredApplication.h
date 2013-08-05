#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CRequiredApplication
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CRequiredApplication

#include "type_.CNotifyPropertyChangeBase.h"


namespace CMSD
{

class CRequiredApplication : public ::CMSD::CNotifyPropertyChangeBase
{
public:
	CMSD_EXPORT CRequiredApplication(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CRequiredApplication(CRequiredApplication const& init);
	void operator=(CRequiredApplication const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CRequiredApplication); }
	MemberElement<xs::CstringType, _altova_mi_altova_CRequiredApplication_altova_Name> Name;
	struct Name { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CRequiredApplication_altova_Description> Description;
	struct Description { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CRequiredApplication_altova_Version> Version;
	struct Version { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CRequiredApplication_altova_OperatingSystem> OperatingSystem;
	struct OperatingSystem { typedef Iterator<xs::CstringType> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CRequiredApplication
