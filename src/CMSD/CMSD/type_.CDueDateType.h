#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CDueDateType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CDueDateType



namespace CMSD
{

class CDueDateType : public TypeBase
{
public:
	CMSD_EXPORT CDueDateType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CDueDateType(CDueDateType const& init);
	void operator=(CDueDateType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CDueDateType); }
	MemberElement<CschemaType, _altova_mi_altova_CDueDateType_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CDueDateType
