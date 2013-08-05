#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPartQuantityType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPartQuantityType



namespace CMSD
{

class CPartQuantityType : public TypeBase
{
public:
	CMSD_EXPORT CPartQuantityType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CPartQuantityType(CPartQuantityType const& init);
	void operator=(CPartQuantityType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CPartQuantityType); }
	MemberElement<CschemaType, _altova_mi_altova_CPartQuantityType_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPartQuantityType
