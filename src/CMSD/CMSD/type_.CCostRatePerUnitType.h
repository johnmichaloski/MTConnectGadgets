#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCostRatePerUnitType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCostRatePerUnitType



namespace CMSD
{

class CCostRatePerUnitType : public TypeBase
{
public:
	CMSD_EXPORT CCostRatePerUnitType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CCostRatePerUnitType(CCostRatePerUnitType const& init);
	void operator=(CCostRatePerUnitType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CCostRatePerUnitType); }
	MemberElement<CschemaType, _altova_mi_altova_CCostRatePerUnitType_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCostRatePerUnitType
