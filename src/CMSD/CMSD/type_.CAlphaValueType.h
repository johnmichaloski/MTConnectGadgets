#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CAlphaValueType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CAlphaValueType



namespace CMSD
{

class CAlphaValueType : public TypeBase
{
public:
	CMSD_EXPORT CAlphaValueType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CAlphaValueType(CAlphaValueType const& init);
	void operator=(CAlphaValueType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CAlphaValueType); }
	MemberElement<CschemaType, _altova_mi_altova_CAlphaValueType_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CAlphaValueType
