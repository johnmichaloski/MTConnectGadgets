#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CValueType6
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CValueType6



namespace CMSD
{

class CValueType6 : public TypeBase
{
public:
	CMSD_EXPORT CValueType6(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CValueType6(CValueType6 const& init);
	void operator=(CValueType6 const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CValueType6); }
	MemberElement<CschemaType, _altova_mi_altova_CValueType6_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CValueType6
