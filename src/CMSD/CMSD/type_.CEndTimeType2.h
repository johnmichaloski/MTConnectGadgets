#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CEndTimeType2
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CEndTimeType2



namespace CMSD
{

class CEndTimeType2 : public TypeBase
{
public:
	CMSD_EXPORT CEndTimeType2(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CEndTimeType2(CEndTimeType2 const& init);
	void operator=(CEndTimeType2 const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CEndTimeType2); }
	MemberElement<CschemaType, _altova_mi_altova_CEndTimeType2_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CEndTimeType2
