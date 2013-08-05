#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CsimpleContentType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CsimpleContentType

#include "type_xs.Cannotated.h"


namespace CMSD
{

class CsimpleContentType : public ::CMSD::xs::Cannotated
{
public:
	CMSD_EXPORT CsimpleContentType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CsimpleContentType(CsimpleContentType const& init);
	void operator=(CsimpleContentType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CsimpleContentType); }
	MemberElement<xs::CsimpleRestrictionType, _altova_mi_altova_CsimpleContentType_altova_restriction> restriction;
	struct restriction { typedef Iterator<xs::CsimpleRestrictionType> iterator; };
	MemberElement<xs::CsimpleExtensionType, _altova_mi_altova_CsimpleContentType_altova_extension> extension;
	struct extension { typedef Iterator<xs::CsimpleExtensionType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CsimpleContentType
