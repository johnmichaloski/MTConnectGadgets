#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CValueType3
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CValueType3



namespace CMSD
{

class CValueType3 : public TypeBase
{
public:
	CMSD_EXPORT CValueType3(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CValueType3(CValueType3 const& init);
	void operator=(CValueType3 const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CValueType3); }
	MemberElement<CschemaType, _altova_mi_altova_CValueType3_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CValueType3
