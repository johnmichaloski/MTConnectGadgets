#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CQuantityOnHandType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CQuantityOnHandType



namespace CMSD
{

class CQuantityOnHandType : public TypeBase
{
public:
	CMSD_EXPORT CQuantityOnHandType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CQuantityOnHandType(CQuantityOnHandType const& init);
	void operator=(CQuantityOnHandType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CQuantityOnHandType); }
	MemberElement<CschemaType, _altova_mi_altova_CQuantityOnHandType_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CQuantityOnHandType
