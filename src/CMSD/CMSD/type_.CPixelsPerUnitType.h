#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPixelsPerUnitType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPixelsPerUnitType



namespace CMSD
{

class CPixelsPerUnitType : public TypeBase
{
public:
	CMSD_EXPORT CPixelsPerUnitType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CPixelsPerUnitType(CPixelsPerUnitType const& init);
	void operator=(CPixelsPerUnitType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CPixelsPerUnitType); }
	MemberElement<CschemaType, _altova_mi_altova_CPixelsPerUnitType_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPixelsPerUnitType
