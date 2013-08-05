#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CWidthType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CWidthType



namespace CMSD
{

class CWidthType : public TypeBase
{
public:
	CMSD_EXPORT CWidthType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CWidthType(CWidthType const& init);
	void operator=(CWidthType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CWidthType); }
	MemberElement<CschemaType, _altova_mi_altova_CWidthType_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CWidthType
