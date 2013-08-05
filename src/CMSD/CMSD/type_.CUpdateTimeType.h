#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CUpdateTimeType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CUpdateTimeType



namespace CMSD
{

class CUpdateTimeType : public TypeBase
{
public:
	CMSD_EXPORT CUpdateTimeType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CUpdateTimeType(CUpdateTimeType const& init);
	void operator=(CUpdateTimeType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CUpdateTimeType); }
	MemberElement<CschemaType, _altova_mi_altova_CUpdateTimeType_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CUpdateTimeType
