#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CXPercentType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CXPercentType



namespace CMSD
{

class CXPercentType : public TypeBase
{
public:
	CMSD_EXPORT CXPercentType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CXPercentType(CXPercentType const& init);
	void operator=(CXPercentType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CXPercentType); }
	MemberElement<CschemaType, _altova_mi_altova_CXPercentType_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CXPercentType
