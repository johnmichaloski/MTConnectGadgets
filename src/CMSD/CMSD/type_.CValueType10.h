#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CValueType10
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CValueType10



namespace CMSD
{

class CValueType10 : public TypeBase
{
public:
	CMSD_EXPORT CValueType10(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CValueType10(CValueType10 const& init);
	void operator=(CValueType10 const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CValueType10); }
	MemberElement<CschemaType, _altova_mi_altova_CValueType10_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CValueType10
