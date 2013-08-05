#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CValueType11
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CValueType11



namespace CMSD
{

class CValueType11 : public TypeBase
{
public:
	CMSD_EXPORT CValueType11(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CValueType11(CValueType11 const& init);
	void operator=(CValueType11 const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CValueType11); }
	MemberElement<CschemaType, _altova_mi_altova_CValueType11_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CValueType11
