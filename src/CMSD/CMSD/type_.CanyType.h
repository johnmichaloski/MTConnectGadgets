#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CanyType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CanyType

#include "type_xs.Cwildcard.h"


namespace CMSD
{

class CanyType : public ::CMSD::xs::Cwildcard
{
public:
	CMSD_EXPORT CanyType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CanyType(CanyType const& init);
	void operator=(CanyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CanyType); }

	MemberAttribute<unsigned __int64,_altova_mi_altova_CanyType_altova_minOccurs, 0, 0> minOccurs;	// minOccurs CnonNegativeInteger
	MemberAttribute<string_type,_altova_mi_altova_CanyType_altova_maxOccurs, 1, 1> maxOccurs;	// maxOccurs CallNNI
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CanyType
