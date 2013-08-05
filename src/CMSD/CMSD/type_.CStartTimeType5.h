#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CStartTimeType5
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CStartTimeType5



namespace CMSD
{

class CStartTimeType5 : public TypeBase
{
public:
	CMSD_EXPORT CStartTimeType5(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CStartTimeType5(CStartTimeType5 const& init);
	void operator=(CStartTimeType5 const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CStartTimeType5); }
	MemberElement<CschemaType, _altova_mi_altova_CStartTimeType5_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CStartTimeType5
