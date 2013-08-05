#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CTimeType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CTimeType



namespace CMSD
{

class CTimeType : public TypeBase
{
public:
	CMSD_EXPORT CTimeType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CTimeType(CTimeType const& init);
	void operator=(CTimeType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CTimeType); }
	MemberElement<CschemaType, _altova_mi_altova_CTimeType_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CTimeType
