#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CannotationType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CannotationType

#include "type_xs.CopenAttrs.h"


namespace CMSD
{

class CannotationType : public ::CMSD::xs::CopenAttrs
{
public:
	CMSD_EXPORT CannotationType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CannotationType(CannotationType const& init);
	void operator=(CannotationType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CannotationType); }

	MemberAttribute<string_type,_altova_mi_altova_CannotationType_altova_id, 0, 0> id;	// id CID
	MemberElement<CappinfoType, _altova_mi_altova_CannotationType_altova_appinfo> appinfo;
	struct appinfo { typedef Iterator<CappinfoType> iterator; };
	MemberElement<CdocumentationType, _altova_mi_altova_CannotationType_altova_documentation> documentation;
	struct documentation { typedef Iterator<CdocumentationType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CannotationType
