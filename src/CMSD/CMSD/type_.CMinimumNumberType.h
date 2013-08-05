#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CMinimumNumberType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CMinimumNumberType



namespace CMSD
{

class CMinimumNumberType : public TypeBase
{
public:
	CMSD_EXPORT CMinimumNumberType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CMinimumNumberType(CMinimumNumberType const& init);
	void operator=(CMinimumNumberType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CMinimumNumberType); }
	MemberElement<CschemaType, _altova_mi_altova_CMinimumNumberType_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CMinimumNumberType
