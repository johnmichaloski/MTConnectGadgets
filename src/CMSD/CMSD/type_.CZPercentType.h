#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CZPercentType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CZPercentType



namespace CMSD
{

class CZPercentType : public TypeBase
{
public:
	CMSD_EXPORT CZPercentType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CZPercentType(CZPercentType const& init);
	void operator=(CZPercentType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CZPercentType); }
	MemberElement<CschemaType, _altova_mi_altova_CZPercentType_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CZPercentType
