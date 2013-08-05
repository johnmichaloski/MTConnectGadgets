#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPiecesPerPackageType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPiecesPerPackageType



namespace CMSD
{

class CPiecesPerPackageType : public TypeBase
{
public:
	CMSD_EXPORT CPiecesPerPackageType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CPiecesPerPackageType(CPiecesPerPackageType const& init);
	void operator=(CPiecesPerPackageType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CPiecesPerPackageType); }
	MemberElement<CschemaType, _altova_mi_altova_CPiecesPerPackageType_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPiecesPerPackageType
