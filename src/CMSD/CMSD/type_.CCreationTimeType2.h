#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCreationTimeType2
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCreationTimeType2



namespace CMSD
{

class CCreationTimeType2 : public TypeBase
{
public:
	CMSD_EXPORT CCreationTimeType2(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CCreationTimeType2(CCreationTimeType2 const& init);
	void operator=(CCreationTimeType2 const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CCreationTimeType2); }
	MemberElement<CschemaType, _altova_mi_altova_CCreationTimeType2_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCreationTimeType2
