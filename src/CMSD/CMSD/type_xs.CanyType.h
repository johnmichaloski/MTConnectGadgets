#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CanyType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CanyType



namespace CMSD
{

namespace xs
{	

class CanyType : public TypeBase
{
public:
	CMSD_EXPORT CanyType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CanyType(CanyType const& init);
	void operator=(CanyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_xs_altova_CanyType); }
	CMSD_EXPORT void operator=(const string_type& value);
	CMSD_EXPORT operator string_type();
	CMSD_EXPORT void SetXsiType();
};



} // namespace xs

}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CanyType
