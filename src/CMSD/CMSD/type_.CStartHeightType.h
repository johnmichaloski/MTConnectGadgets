#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CStartHeightType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CStartHeightType



namespace CMSD
{

class CStartHeightType : public TypeBase
{
public:
	CMSD_EXPORT CStartHeightType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CStartHeightType(CStartHeightType const& init);
	void operator=(CStartHeightType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CStartHeightType); }
	MemberElement<CschemaType, _altova_mi_altova_CStartHeightType_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CStartHeightType
