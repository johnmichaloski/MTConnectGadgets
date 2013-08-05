#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CEffectiveStartDateType2
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CEffectiveStartDateType2



namespace CMSD
{

class CEffectiveStartDateType2 : public TypeBase
{
public:
	CMSD_EXPORT CEffectiveStartDateType2(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CEffectiveStartDateType2(CEffectiveStartDateType2 const& init);
	void operator=(CEffectiveStartDateType2 const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CEffectiveStartDateType2); }
	MemberElement<CschemaType, _altova_mi_altova_CEffectiveStartDateType2_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CEffectiveStartDateType2
