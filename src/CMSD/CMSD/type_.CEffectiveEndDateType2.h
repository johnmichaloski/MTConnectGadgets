#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CEffectiveEndDateType2
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CEffectiveEndDateType2



namespace CMSD
{

class CEffectiveEndDateType2 : public TypeBase
{
public:
	CMSD_EXPORT CEffectiveEndDateType2(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CEffectiveEndDateType2(CEffectiveEndDateType2 const& init);
	void operator=(CEffectiveEndDateType2 const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CEffectiveEndDateType2); }
	MemberElement<CschemaType, _altova_mi_altova_CEffectiveEndDateType2_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CEffectiveEndDateType2
