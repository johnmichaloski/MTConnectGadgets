#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CYType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CYType



namespace CMSD
{

class CYType : public TypeBase
{
public:
	CMSD_EXPORT CYType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CYType(CYType const& init);
	void operator=(CYType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CYType); }
	MemberElement<CschemaType, _altova_mi_altova_CYType_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CYType
