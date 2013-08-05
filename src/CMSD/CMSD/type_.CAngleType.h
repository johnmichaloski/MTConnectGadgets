#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CAngleType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CAngleType



namespace CMSD
{

class CAngleType : public TypeBase
{
public:
	CMSD_EXPORT CAngleType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CAngleType(CAngleType const& init);
	void operator=(CAngleType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CAngleType); }
	MemberElement<CschemaType, _altova_mi_altova_CAngleType_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CAngleType
