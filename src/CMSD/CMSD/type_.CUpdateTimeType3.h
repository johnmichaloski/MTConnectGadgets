#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CUpdateTimeType3
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CUpdateTimeType3



namespace CMSD
{

class CUpdateTimeType3 : public TypeBase
{
public:
	CMSD_EXPORT CUpdateTimeType3(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CUpdateTimeType3(CUpdateTimeType3 const& init);
	void operator=(CUpdateTimeType3 const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CUpdateTimeType3); }
	MemberElement<CschemaType, _altova_mi_altova_CUpdateTimeType3_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CUpdateTimeType3
