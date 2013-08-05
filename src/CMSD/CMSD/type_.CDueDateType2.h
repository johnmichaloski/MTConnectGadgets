#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CDueDateType2
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CDueDateType2



namespace CMSD
{

class CDueDateType2 : public TypeBase
{
public:
	CMSD_EXPORT CDueDateType2(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CDueDateType2(CDueDateType2 const& init);
	void operator=(CDueDateType2 const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CDueDateType2); }
	MemberElement<CschemaType, _altova_mi_altova_CDueDateType2_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CDueDateType2
