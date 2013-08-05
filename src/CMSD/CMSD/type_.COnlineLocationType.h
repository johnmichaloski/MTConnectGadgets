#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_COnlineLocationType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_COnlineLocationType



namespace CMSD
{

class COnlineLocationType : public TypeBase
{
public:
	CMSD_EXPORT COnlineLocationType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT COnlineLocationType(COnlineLocationType const& init);
	void operator=(COnlineLocationType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_COnlineLocationType); }
	MemberElement<CschemaType, _altova_mi_altova_COnlineLocationType_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_COnlineLocationType
