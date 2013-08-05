#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CTextAngleType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CTextAngleType



namespace CMSD
{

class CTextAngleType : public TypeBase
{
public:
	CMSD_EXPORT CTextAngleType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CTextAngleType(CTextAngleType const& init);
	void operator=(CTextAngleType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CTextAngleType); }
	MemberElement<CschemaType, _altova_mi_altova_CTextAngleType_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CTextAngleType
