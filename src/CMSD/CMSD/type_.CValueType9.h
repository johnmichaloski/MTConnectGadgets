#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CValueType9
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CValueType9



namespace CMSD
{

class CValueType9 : public TypeBase
{
public:
	CMSD_EXPORT CValueType9(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CValueType9(CValueType9 const& init);
	void operator=(CValueType9 const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CValueType9); }
	MemberElement<CschemaType, _altova_mi_altova_CValueType9_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CValueType9
