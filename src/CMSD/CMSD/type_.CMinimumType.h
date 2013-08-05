#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CMinimumType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CMinimumType



namespace CMSD
{

class CMinimumType : public TypeBase
{
public:
	CMSD_EXPORT CMinimumType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CMinimumType(CMinimumType const& init);
	void operator=(CMinimumType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CMinimumType); }
	MemberElement<CschemaType, _altova_mi_altova_CMinimumType_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CMinimumType
