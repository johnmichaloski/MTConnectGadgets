#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CValueType7
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CValueType7



namespace CMSD
{

class CValueType7 : public TypeBase
{
public:
	CMSD_EXPORT CValueType7(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CValueType7(CValueType7 const& init);
	void operator=(CValueType7 const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CValueType7); }
	MemberElement<CschemaType, _altova_mi_altova_CValueType7_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CValueType7
