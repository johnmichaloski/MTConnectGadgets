#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CMaximumNumberType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CMaximumNumberType



namespace CMSD
{

class CMaximumNumberType : public TypeBase
{
public:
	CMSD_EXPORT CMaximumNumberType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CMaximumNumberType(CMaximumNumberType const& init);
	void operator=(CMaximumNumberType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CMaximumNumberType); }
	MemberElement<CschemaType, _altova_mi_altova_CMaximumNumberType_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CMaximumNumberType
