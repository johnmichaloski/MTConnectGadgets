#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CIntegerType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CIntegerType



namespace CMSD
{

class CIntegerType : public TypeBase
{
public:
	CMSD_EXPORT CIntegerType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CIntegerType(CIntegerType const& init);
	void operator=(CIntegerType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CIntegerType); }
	MemberElement<CschemaType, _altova_mi_altova_CIntegerType_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CIntegerType
