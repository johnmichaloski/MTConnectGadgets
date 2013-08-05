#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CRepetitionCountType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CRepetitionCountType



namespace CMSD
{

class CRepetitionCountType : public TypeBase
{
public:
	CMSD_EXPORT CRepetitionCountType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CRepetitionCountType(CRepetitionCountType const& init);
	void operator=(CRepetitionCountType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CRepetitionCountType); }
	MemberElement<CschemaType, _altova_mi_altova_CRepetitionCountType_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CRepetitionCountType
