#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CUpdateTimeType4
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CUpdateTimeType4



namespace CMSD
{

class CUpdateTimeType4 : public TypeBase
{
public:
	CMSD_EXPORT CUpdateTimeType4(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CUpdateTimeType4(CUpdateTimeType4 const& init);
	void operator=(CUpdateTimeType4 const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CUpdateTimeType4); }
	MemberElement<CschemaType, _altova_mi_altova_CUpdateTimeType4_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CUpdateTimeType4
