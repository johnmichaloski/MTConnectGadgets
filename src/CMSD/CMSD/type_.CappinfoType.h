#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CappinfoType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CappinfoType



namespace CMSD
{

class CappinfoType : public TypeBase
{
public:
	CMSD_EXPORT CappinfoType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CappinfoType(CappinfoType const& init);
	void operator=(CappinfoType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CappinfoType); }
	CMSD_EXPORT void operator=(const string_type& value);
	CMSD_EXPORT operator string_type();

	MemberAttribute<string_type,_altova_mi_altova_CappinfoType_altova_source, 0, 0> source;	// source CanyURI
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CappinfoType
