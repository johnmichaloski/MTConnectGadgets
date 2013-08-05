#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCMSDDecimalType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCMSDDecimalType



namespace CMSD
{

class CCMSDDecimalType : public TypeBase
{
public:
	CMSD_EXPORT CCMSDDecimalType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CCMSDDecimalType(CCMSDDecimalType const& init);
	void operator=(CCMSDDecimalType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CCMSDDecimalType); }
	MemberElement<CschemaType, _altova_mi_altova_CCMSDDecimalType_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCMSDDecimalType
