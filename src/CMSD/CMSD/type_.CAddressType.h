#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CAddressType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CAddressType



namespace CMSD
{

class CAddressType : public TypeBase
{
public:
	CMSD_EXPORT CAddressType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CAddressType(CAddressType const& init);
	void operator=(CAddressType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CAddressType); }
	MemberElement<CschemaType, _altova_mi_altova_CAddressType_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CAddressType
