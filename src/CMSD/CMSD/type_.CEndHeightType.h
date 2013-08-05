#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CEndHeightType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CEndHeightType



namespace CMSD
{

class CEndHeightType : public TypeBase
{
public:
	CMSD_EXPORT CEndHeightType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CEndHeightType(CEndHeightType const& init);
	void operator=(CEndHeightType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CEndHeightType); }
	MemberElement<CschemaType, _altova_mi_altova_CEndHeightType_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CEndHeightType
