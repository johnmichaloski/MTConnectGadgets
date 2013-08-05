#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CValueType5
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CValueType5



namespace CMSD
{

class CValueType5 : public TypeBase
{
public:
	CMSD_EXPORT CValueType5(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CValueType5(CValueType5 const& init);
	void operator=(CValueType5 const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CValueType5); }
	MemberElement<CschemaType, _altova_mi_altova_CValueType5_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CValueType5
