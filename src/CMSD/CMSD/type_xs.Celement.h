#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_Celement
#define _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_Celement

#include "type_xs.Cannotated.h"


namespace CMSD
{

namespace xs
{	

class Celement : public ::CMSD::xs::Cannotated
{
public:
	CMSD_EXPORT Celement(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT Celement(Celement const& init);
	void operator=(Celement const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_xs_altova_Celement); }

	MemberAttribute<string_type,_altova_mi_xs_altova_Celement_altova_name, 0, 0> name;	// name CNCName

	MemberAttribute<string_type,_altova_mi_xs_altova_Celement_altova_ref, 0, 0> ref;	// ref CQName

	MemberAttribute<string_type,_altova_mi_xs_altova_Celement_altova_type, 0, 0> type;	// type CQName

	MemberAttribute<string_type,_altova_mi_xs_altova_Celement_altova_substitutionGroup, 0, 0> substitutionGroup;	// substitutionGroup CQName

	MemberAttribute<unsigned __int64,_altova_mi_xs_altova_Celement_altova_minOccurs, 0, 0> minOccurs;	// minOccurs CnonNegativeInteger
	MemberAttribute<string_type,_altova_mi_xs_altova_Celement_altova_maxOccurs, 1, 1> maxOccurs;	// maxOccurs CallNNI

	MemberAttribute<string_type,_altova_mi_xs_altova_Celement_altova_default2, 0, 0> default2;	// default Cstring

	MemberAttribute<string_type,_altova_mi_xs_altova_Celement_altova_fixed, 0, 0> fixed;	// fixed Cstring

	MemberAttribute<bool,_altova_mi_xs_altova_Celement_altova_nillable, 0, 0> nillable;	// nillable Cboolean

	MemberAttribute<bool,_altova_mi_xs_altova_Celement_altova_abstract, 0, 0> abstract;	// abstract Cboolean
	MemberAttribute<string_type,_altova_mi_xs_altova_Celement_altova_final, 1, 3> final;	// final CderivationSet
	MemberAttribute<string_type,_altova_mi_xs_altova_Celement_altova_block, 1, 4> block;	// block CblockSet
	MemberAttribute<string_type,_altova_mi_xs_altova_Celement_altova_form, 0, 2> form;	// form CformChoice
	MemberElement<xs::ClocalSimpleType, _altova_mi_xs_altova_Celement_altova_simpleType> simpleType;
	struct simpleType { typedef Iterator<xs::ClocalSimpleType> iterator; };
	MemberElement<xs::ClocalComplexType, _altova_mi_xs_altova_Celement_altova_complexType> complexType;
	struct complexType { typedef Iterator<xs::ClocalComplexType> iterator; };
	MemberElement<xs::Ckeybase, _altova_mi_xs_altova_Celement_altova_unique> unique;
	struct unique { typedef Iterator<xs::Ckeybase> iterator; };
	MemberElement<xs::Ckeybase, _altova_mi_xs_altova_Celement_altova_key> key;
	struct key { typedef Iterator<xs::Ckeybase> iterator; };
	MemberElement<CkeyrefType, _altova_mi_xs_altova_Celement_altova_keyref> keyref;
	struct keyref { typedef Iterator<CkeyrefType> iterator; };
	CMSD_EXPORT void SetXsiType();
};



} // namespace xs

}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_Celement
