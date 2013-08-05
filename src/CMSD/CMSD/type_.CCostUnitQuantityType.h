#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCostUnitQuantityType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCostUnitQuantityType



namespace CMSD
{

class CCostUnitQuantityType : public TypeBase
{
public:
	CMSD_EXPORT CCostUnitQuantityType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CCostUnitQuantityType(CCostUnitQuantityType const& init);
	void operator=(CCostUnitQuantityType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CCostUnitQuantityType); }
	MemberElement<CschemaType, _altova_mi_altova_CCostUnitQuantityType_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCostUnitQuantityType
