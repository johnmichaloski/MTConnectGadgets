#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CcomplexContentType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CcomplexContentType

#include "type_xs.Cannotated.h"


namespace CMSD
{

class CcomplexContentType : public ::CMSD::xs::Cannotated
{
public:
	CMSD_EXPORT CcomplexContentType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CcomplexContentType(CcomplexContentType const& init);
	void operator=(CcomplexContentType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CcomplexContentType); }

	MemberAttribute<bool,_altova_mi_altova_CcomplexContentType_altova_mixed, 0, 0> mixed;	// mixed Cboolean
	MemberElement<xs::CcomplexRestrictionType, _altova_mi_altova_CcomplexContentType_altova_restriction> restriction;
	struct restriction { typedef Iterator<xs::CcomplexRestrictionType> iterator; };
	MemberElement<xs::CextensionType, _altova_mi_altova_CcomplexContentType_altova_extension> extension;
	struct extension { typedef Iterator<xs::CextensionType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CcomplexContentType
