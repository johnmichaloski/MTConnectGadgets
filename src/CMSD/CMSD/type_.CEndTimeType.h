#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CEndTimeType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CEndTimeType



namespace CMSD
{

class CEndTimeType : public TypeBase
{
public:
	CMSD_EXPORT CEndTimeType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CEndTimeType(CEndTimeType const& init);
	void operator=(CEndTimeType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CEndTimeType); }
	MemberElement<CschemaType, _altova_mi_altova_CEndTimeType_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CEndTimeType
