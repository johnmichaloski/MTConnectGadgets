#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CWidthType2
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CWidthType2



namespace CMSD
{

class CWidthType2 : public TypeBase
{
public:
	CMSD_EXPORT CWidthType2(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CWidthType2(CWidthType2 const& init);
	void operator=(CWidthType2 const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CWidthType2); }
	MemberElement<CschemaType, _altova_mi_altova_CWidthType2_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CWidthType2
