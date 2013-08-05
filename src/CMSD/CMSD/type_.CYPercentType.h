#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CYPercentType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CYPercentType



namespace CMSD
{

class CYPercentType : public TypeBase
{
public:
	CMSD_EXPORT CYPercentType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CYPercentType(CYPercentType const& init);
	void operator=(CYPercentType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CYPercentType); }
	MemberElement<CschemaType, _altova_mi_altova_CYPercentType_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CYPercentType
