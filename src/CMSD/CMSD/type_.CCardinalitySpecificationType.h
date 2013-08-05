#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCardinalitySpecificationType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCardinalitySpecificationType



namespace CMSD
{

class CCardinalitySpecificationType : public TypeBase
{
public:
	CMSD_EXPORT CCardinalitySpecificationType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CCardinalitySpecificationType(CCardinalitySpecificationType const& init);
	void operator=(CCardinalitySpecificationType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CCardinalitySpecificationType); }
	MemberElement<CschemaType, _altova_mi_altova_CCardinalitySpecificationType_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCardinalitySpecificationType
