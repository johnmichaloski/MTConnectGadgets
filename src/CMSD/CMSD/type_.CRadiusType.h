#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CRadiusType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CRadiusType



namespace CMSD
{

class CRadiusType : public TypeBase
{
public:
	CMSD_EXPORT CRadiusType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CRadiusType(CRadiusType const& init);
	void operator=(CRadiusType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CRadiusType); }
	MemberElement<CschemaType, _altova_mi_altova_CRadiusType_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CRadiusType
