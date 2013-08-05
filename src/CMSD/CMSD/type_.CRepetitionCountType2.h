#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CRepetitionCountType2
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CRepetitionCountType2



namespace CMSD
{

class CRepetitionCountType2 : public TypeBase
{
public:
	CMSD_EXPORT CRepetitionCountType2(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CRepetitionCountType2(CRepetitionCountType2 const& init);
	void operator=(CRepetitionCountType2 const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CRepetitionCountType2); }
	MemberElement<CschemaType, _altova_mi_altova_CRepetitionCountType2_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CRepetitionCountType2
