#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CWidthType4
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CWidthType4



namespace CMSD
{

class CWidthType4 : public TypeBase
{
public:
	CMSD_EXPORT CWidthType4(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CWidthType4(CWidthType4 const& init);
	void operator=(CWidthType4 const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CWidthType4); }
	MemberElement<CschemaType, _altova_mi_altova_CWidthType4_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CWidthType4
