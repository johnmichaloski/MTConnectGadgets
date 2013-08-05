#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CUpdateTimeType2
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CUpdateTimeType2



namespace CMSD
{

class CUpdateTimeType2 : public TypeBase
{
public:
	CMSD_EXPORT CUpdateTimeType2(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CUpdateTimeType2(CUpdateTimeType2 const& init);
	void operator=(CUpdateTimeType2 const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CUpdateTimeType2); }
	MemberElement<CschemaType, _altova_mi_altova_CUpdateTimeType2_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CUpdateTimeType2
