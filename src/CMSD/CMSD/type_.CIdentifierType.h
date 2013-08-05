#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CIdentifierType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CIdentifierType



namespace CMSD
{

class CIdentifierType : public TypeBase
{
public:
	CMSD_EXPORT CIdentifierType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CIdentifierType(CIdentifierType const& init);
	void operator=(CIdentifierType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CIdentifierType); }
	MemberElement<CschemaType, _altova_mi_altova_CIdentifierType_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CIdentifierType
