#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CStartTimeType4
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CStartTimeType4



namespace CMSD
{

class CStartTimeType4 : public TypeBase
{
public:
	CMSD_EXPORT CStartTimeType4(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CStartTimeType4(CStartTimeType4 const& init);
	void operator=(CStartTimeType4 const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CStartTimeType4); }
	MemberElement<CschemaType, _altova_mi_altova_CStartTimeType4_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CStartTimeType4
