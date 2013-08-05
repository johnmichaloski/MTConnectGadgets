#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CValueType2
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CValueType2



namespace CMSD
{

class CValueType2 : public TypeBase
{
public:
	CMSD_EXPORT CValueType2(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CValueType2(CValueType2 const& init);
	void operator=(CValueType2 const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CValueType2); }
	MemberElement<CschemaType, _altova_mi_altova_CValueType2_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CValueType2
