#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CUpdateTimeType5
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CUpdateTimeType5



namespace CMSD
{

class CUpdateTimeType5 : public TypeBase
{
public:
	CMSD_EXPORT CUpdateTimeType5(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CUpdateTimeType5(CUpdateTimeType5 const& init);
	void operator=(CUpdateTimeType5 const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CUpdateTimeType5); }
	MemberElement<CschemaType, _altova_mi_altova_CUpdateTimeType5_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CUpdateTimeType5
