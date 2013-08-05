#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CNonNegativeIntegerType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CNonNegativeIntegerType



namespace CMSD
{

class CNonNegativeIntegerType : public TypeBase
{
public:
	CMSD_EXPORT CNonNegativeIntegerType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CNonNegativeIntegerType(CNonNegativeIntegerType const& init);
	void operator=(CNonNegativeIntegerType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CNonNegativeIntegerType); }
	MemberElement<CschemaType, _altova_mi_altova_CNonNegativeIntegerType_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CNonNegativeIntegerType
