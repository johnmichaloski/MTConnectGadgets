#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CValueType4
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CValueType4



namespace CMSD
{

class CValueType4 : public TypeBase
{
public:
	CMSD_EXPORT CValueType4(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CValueType4(CValueType4 const& init);
	void operator=(CValueType4 const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CValueType4); }
	MemberElement<CschemaType, _altova_mi_altova_CValueType4_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CValueType4
