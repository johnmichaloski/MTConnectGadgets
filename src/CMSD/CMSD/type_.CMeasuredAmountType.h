#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CMeasuredAmountType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CMeasuredAmountType



namespace CMSD
{

class CMeasuredAmountType : public TypeBase
{
public:
	CMSD_EXPORT CMeasuredAmountType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CMeasuredAmountType(CMeasuredAmountType const& init);
	void operator=(CMeasuredAmountType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CMeasuredAmountType); }
	MemberElement<CschemaType, _altova_mi_altova_CMeasuredAmountType_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CMeasuredAmountType
