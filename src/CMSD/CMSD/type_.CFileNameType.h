#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CFileNameType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CFileNameType



namespace CMSD
{

class CFileNameType : public TypeBase
{
public:
	CMSD_EXPORT CFileNameType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CFileNameType(CFileNameType const& init);
	void operator=(CFileNameType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CFileNameType); }
	MemberElement<CschemaType, _altova_mi_altova_CFileNameType_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CFileNameType
