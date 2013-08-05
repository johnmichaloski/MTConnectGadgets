#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CItemQuantityType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CItemQuantityType



namespace CMSD
{

class CItemQuantityType : public TypeBase
{
public:
	CMSD_EXPORT CItemQuantityType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CItemQuantityType(CItemQuantityType const& init);
	void operator=(CItemQuantityType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CItemQuantityType); }
	MemberElement<CschemaType, _altova_mi_altova_CItemQuantityType_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CItemQuantityType
