#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CYOffsetType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CYOffsetType



namespace CMSD
{

class CYOffsetType : public TypeBase
{
public:
	CMSD_EXPORT CYOffsetType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CYOffsetType(CYOffsetType const& init);
	void operator=(CYOffsetType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CYOffsetType); }
	MemberElement<CschemaType, _altova_mi_altova_CYOffsetType_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CYOffsetType
