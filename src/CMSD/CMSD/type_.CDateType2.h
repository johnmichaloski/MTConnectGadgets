#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CDateType2
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CDateType2



namespace CMSD
{

class CDateType2 : public TypeBase
{
public:
	CMSD_EXPORT CDateType2(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CDateType2(CDateType2 const& init);
	void operator=(CDateType2 const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CDateType2); }
	MemberElement<CschemaType, _altova_mi_altova_CDateType2_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CDateType2
