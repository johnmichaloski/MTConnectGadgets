#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CLagPartsCompleteType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CLagPartsCompleteType



namespace CMSD
{

class CLagPartsCompleteType : public TypeBase
{
public:
	CMSD_EXPORT CLagPartsCompleteType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CLagPartsCompleteType(CLagPartsCompleteType const& init);
	void operator=(CLagPartsCompleteType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CLagPartsCompleteType); }
	MemberElement<CschemaType, _altova_mi_altova_CLagPartsCompleteType_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CLagPartsCompleteType
