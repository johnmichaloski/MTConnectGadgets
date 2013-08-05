#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_Ckeybase
#define _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_Ckeybase

#include "type_xs.Cannotated.h"


namespace CMSD
{

namespace xs
{	

class Ckeybase : public ::CMSD::xs::Cannotated
{
public:
	CMSD_EXPORT Ckeybase(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT Ckeybase(Ckeybase const& init);
	void operator=(Ckeybase const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_xs_altova_Ckeybase); }

	MemberAttribute<string_type,_altova_mi_xs_altova_Ckeybase_altova_name, 0, 0> name;	// name CNCName
	MemberElement<xs::CselectorType, _altova_mi_xs_altova_Ckeybase_altova_selector> selector;
	struct selector { typedef Iterator<xs::CselectorType> iterator; };
	MemberElement<CfieldType, _altova_mi_xs_altova_Ckeybase_altova_field> field;
	struct field { typedef Iterator<CfieldType> iterator; };
	CMSD_EXPORT void SetXsiType();
};



} // namespace xs

}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_Ckeybase
