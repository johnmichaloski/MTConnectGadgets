#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCreationTimeType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCreationTimeType



namespace CMSD
{

class CCreationTimeType : public TypeBase
{
public:
	CMSD_EXPORT CCreationTimeType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CCreationTimeType(CCreationTimeType const& init);
	void operator=(CCreationTimeType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CCreationTimeType); }
	MemberElement<CschemaType, _altova_mi_altova_CCreationTimeType_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCreationTimeType
