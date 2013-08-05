#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_ClistType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_ClistType

#include "type_xs.Cannotated.h"


namespace CMSD
{

class ClistType : public ::CMSD::xs::Cannotated
{
public:
	CMSD_EXPORT ClistType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT ClistType(ClistType const& init);
	void operator=(ClistType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_ClistType); }

	MemberAttribute<string_type,_altova_mi_altova_ClistType_altova_itemType, 0, 0> itemType;	// itemType CQName
	MemberElement<xs::ClocalSimpleType, _altova_mi_altova_ClistType_altova_simpleType> simpleType;
	struct simpleType { typedef Iterator<xs::ClocalSimpleType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_ClistType
