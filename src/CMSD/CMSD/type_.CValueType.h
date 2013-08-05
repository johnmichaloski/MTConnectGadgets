#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CValueType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CValueType



namespace CMSD
{

class CValueType : public TypeBase
{
public:
	CMSD_EXPORT CValueType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CValueType(CValueType const& init);
	void operator=(CValueType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CValueType); }
	MemberElement<CschemaType, _altova_mi_altova_CValueType_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CValueType
