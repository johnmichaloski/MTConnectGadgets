#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CStartTimeType2
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CStartTimeType2



namespace CMSD
{

class CStartTimeType2 : public TypeBase
{
public:
	CMSD_EXPORT CStartTimeType2(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CStartTimeType2(CStartTimeType2 const& init);
	void operator=(CStartTimeType2 const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CStartTimeType2); }
	MemberElement<CschemaType, _altova_mi_altova_CStartTimeType2_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CStartTimeType2
