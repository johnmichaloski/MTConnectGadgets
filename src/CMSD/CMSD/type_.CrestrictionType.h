#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CrestrictionType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CrestrictionType

#include "type_xs.Cannotated.h"


namespace CMSD
{

class CrestrictionType : public ::CMSD::xs::Cannotated
{
public:
	CMSD_EXPORT CrestrictionType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CrestrictionType(CrestrictionType const& init);
	void operator=(CrestrictionType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CrestrictionType); }

	MemberAttribute<string_type,_altova_mi_altova_CrestrictionType_altova_base, 0, 0> base;	// base CQName
	MemberElement<xs::ClocalSimpleType, _altova_mi_altova_CrestrictionType_altova_simpleType> simpleType;
	struct simpleType { typedef Iterator<xs::ClocalSimpleType> iterator; };
	MemberElement<xs::Cfacet, _altova_mi_altova_CrestrictionType_altova_minExclusive> minExclusive;
	struct minExclusive { typedef Iterator<xs::Cfacet> iterator; };
	MemberElement<xs::Cfacet, _altova_mi_altova_CrestrictionType_altova_minInclusive> minInclusive;
	struct minInclusive { typedef Iterator<xs::Cfacet> iterator; };
	MemberElement<xs::Cfacet, _altova_mi_altova_CrestrictionType_altova_maxExclusive> maxExclusive;
	struct maxExclusive { typedef Iterator<xs::Cfacet> iterator; };
	MemberElement<xs::Cfacet, _altova_mi_altova_CrestrictionType_altova_maxInclusive> maxInclusive;
	struct maxInclusive { typedef Iterator<xs::Cfacet> iterator; };
	MemberElement<CtotalDigitsType, _altova_mi_altova_CrestrictionType_altova_totalDigits> totalDigits;
	struct totalDigits { typedef Iterator<CtotalDigitsType> iterator; };
	MemberElement<xs::CnumFacet, _altova_mi_altova_CrestrictionType_altova_fractionDigits> fractionDigits;
	struct fractionDigits { typedef Iterator<xs::CnumFacet> iterator; };
	MemberElement<xs::CnumFacet, _altova_mi_altova_CrestrictionType_altova_length> length;
	struct length { typedef Iterator<xs::CnumFacet> iterator; };
	MemberElement<xs::CnumFacet, _altova_mi_altova_CrestrictionType_altova_minLength> minLength;
	struct minLength { typedef Iterator<xs::CnumFacet> iterator; };
	MemberElement<xs::CnumFacet, _altova_mi_altova_CrestrictionType_altova_maxLength> maxLength;
	struct maxLength { typedef Iterator<xs::CnumFacet> iterator; };
	MemberElement<xs::CnoFixedFacet, _altova_mi_altova_CrestrictionType_altova_enumeration> enumeration;
	struct enumeration { typedef Iterator<xs::CnoFixedFacet> iterator; };
	MemberElement<CwhiteSpaceType, _altova_mi_altova_CrestrictionType_altova_whiteSpace> whiteSpace;
	struct whiteSpace { typedef Iterator<CwhiteSpaceType> iterator; };
	MemberElement<CpatternType, _altova_mi_altova_CrestrictionType_altova_pattern> pattern;
	struct pattern { typedef Iterator<CpatternType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CrestrictionType
