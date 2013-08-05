#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CRotationAngleType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CRotationAngleType



namespace CMSD
{

class CRotationAngleType : public TypeBase
{
public:
	CMSD_EXPORT CRotationAngleType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CRotationAngleType(CRotationAngleType const& init);
	void operator=(CRotationAngleType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CRotationAngleType); }
	MemberElement<CschemaType, _altova_mi_altova_CRotationAngleType_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CRotationAngleType
