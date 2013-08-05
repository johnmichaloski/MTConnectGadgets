#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CValueType12
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CValueType12



namespace CMSD
{

class CValueType12 : public TypeBase
{
public:
	CMSD_EXPORT CValueType12(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CValueType12(CValueType12 const& init);
	void operator=(CValueType12 const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CValueType12); }
	MemberElement<CschemaType, _altova_mi_altova_CValueType12_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CValueType12
