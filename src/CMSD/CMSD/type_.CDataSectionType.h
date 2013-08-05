#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CDataSectionType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CDataSectionType



namespace CMSD
{

class CDataSectionType : public TypeBase
{
public:
	CMSD_EXPORT CDataSectionType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CDataSectionType(CDataSectionType const& init);
	void operator=(CDataSectionType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CDataSectionType); }
	MemberElement<CUniqueEntity, _altova_mi_altova_CDataSectionType_altova_UniqueEntity> UniqueEntity;
	struct UniqueEntity { typedef Iterator<CUniqueEntity> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CDataSectionType
