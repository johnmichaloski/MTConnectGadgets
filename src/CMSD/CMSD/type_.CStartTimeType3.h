#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CStartTimeType3
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CStartTimeType3



namespace CMSD
{

class CStartTimeType3 : public TypeBase
{
public:
	CMSD_EXPORT CStartTimeType3(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CStartTimeType3(CStartTimeType3 const& init);
	void operator=(CStartTimeType3 const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CStartTimeType3); }
	MemberElement<CschemaType, _altova_mi_altova_CStartTimeType3_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CStartTimeType3
