#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CZOffsetType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CZOffsetType



namespace CMSD
{

class CZOffsetType : public TypeBase
{
public:
	CMSD_EXPORT CZOffsetType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CZOffsetType(CZOffsetType const& init);
	void operator=(CZOffsetType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CZOffsetType); }
	MemberElement<CschemaType, _altova_mi_altova_CZOffsetType_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CZOffsetType
