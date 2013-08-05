#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CStartTimeType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CStartTimeType



namespace CMSD
{

class CStartTimeType : public TypeBase
{
public:
	CMSD_EXPORT CStartTimeType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CStartTimeType(CStartTimeType const& init);
	void operator=(CStartTimeType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CStartTimeType); }
	MemberElement<CschemaType, _altova_mi_altova_CStartTimeType_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CStartTimeType
