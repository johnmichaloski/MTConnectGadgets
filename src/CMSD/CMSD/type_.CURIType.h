#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CURIType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CURIType



namespace CMSD
{

class CURIType : public TypeBase
{
public:
	CMSD_EXPORT CURIType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CURIType(CURIType const& init);
	void operator=(CURIType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CURIType); }
	MemberElement<CschemaType, _altova_mi_altova_CURIType_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CURIType
