#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CEndTimeType3
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CEndTimeType3



namespace CMSD
{

class CEndTimeType3 : public TypeBase
{
public:
	CMSD_EXPORT CEndTimeType3(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CEndTimeType3(CEndTimeType3 const& init);
	void operator=(CEndTimeType3 const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CEndTimeType3); }
	MemberElement<CschemaType, _altova_mi_altova_CEndTimeType3_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CEndTimeType3
