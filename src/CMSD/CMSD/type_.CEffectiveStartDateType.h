#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CEffectiveStartDateType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CEffectiveStartDateType



namespace CMSD
{

class CEffectiveStartDateType : public TypeBase
{
public:
	CMSD_EXPORT CEffectiveStartDateType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CEffectiveStartDateType(CEffectiveStartDateType const& init);
	void operator=(CEffectiveStartDateType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CEffectiveStartDateType); }
	MemberElement<CschemaType, _altova_mi_altova_CEffectiveStartDateType_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CEffectiveStartDateType
