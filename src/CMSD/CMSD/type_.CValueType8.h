#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CValueType8
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CValueType8



namespace CMSD
{

class CValueType8 : public TypeBase
{
public:
	CMSD_EXPORT CValueType8(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CValueType8(CValueType8 const& init);
	void operator=(CValueType8 const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CValueType8); }
	MemberElement<CschemaType, _altova_mi_altova_CValueType8_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CValueType8
