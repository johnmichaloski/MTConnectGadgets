#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CkeyrefType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CkeyrefType

#include "type_xs.Ckeybase.h"


namespace CMSD
{

class CkeyrefType : public ::CMSD::xs::Ckeybase
{
public:
	CMSD_EXPORT CkeyrefType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CkeyrefType(CkeyrefType const& init);
	void operator=(CkeyrefType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CkeyrefType); }

	MemberAttribute<string_type,_altova_mi_altova_CkeyrefType_altova_refer, 0, 0> refer;	// refer CQName
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CkeyrefType
