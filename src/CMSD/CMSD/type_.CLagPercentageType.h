#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CLagPercentageType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CLagPercentageType



namespace CMSD
{

class CLagPercentageType : public TypeBase
{
public:
	CMSD_EXPORT CLagPercentageType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CLagPercentageType(CLagPercentageType const& init);
	void operator=(CLagPercentageType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CLagPercentageType); }
	MemberElement<CschemaType, _altova_mi_altova_CLagPercentageType_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CLagPercentageType
