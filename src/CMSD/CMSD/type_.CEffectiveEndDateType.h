#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CEffectiveEndDateType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CEffectiveEndDateType



namespace CMSD
{

class CEffectiveEndDateType : public TypeBase
{
public:
	CMSD_EXPORT CEffectiveEndDateType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CEffectiveEndDateType(CEffectiveEndDateType const& init);
	void operator=(CEffectiveEndDateType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CEffectiveEndDateType); }
	MemberElement<CschemaType, _altova_mi_altova_CEffectiveEndDateType_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CEffectiveEndDateType
