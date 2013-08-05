#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CQuantityType2
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CQuantityType2



namespace CMSD
{

class CQuantityType2 : public TypeBase
{
public:
	CMSD_EXPORT CQuantityType2(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CQuantityType2(CQuantityType2 const& init);
	void operator=(CQuantityType2 const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CQuantityType2); }
	MemberElement<CschemaType, _altova_mi_altova_CQuantityType2_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CQuantityType2
