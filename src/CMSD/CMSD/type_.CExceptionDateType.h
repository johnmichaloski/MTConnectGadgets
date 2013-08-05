#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CExceptionDateType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CExceptionDateType



namespace CMSD
{

class CExceptionDateType : public TypeBase
{
public:
	CMSD_EXPORT CExceptionDateType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CExceptionDateType(CExceptionDateType const& init);
	void operator=(CExceptionDateType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CExceptionDateType); }
	MemberElement<CschemaType, _altova_mi_altova_CExceptionDateType_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CExceptionDateType
