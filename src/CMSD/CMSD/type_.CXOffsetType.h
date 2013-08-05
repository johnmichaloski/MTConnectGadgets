#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CXOffsetType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CXOffsetType



namespace CMSD
{

class CXOffsetType : public TypeBase
{
public:
	CMSD_EXPORT CXOffsetType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CXOffsetType(CXOffsetType const& init);
	void operator=(CXOffsetType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CXOffsetType); }
	MemberElement<CschemaType, _altova_mi_altova_CXOffsetType_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CXOffsetType
