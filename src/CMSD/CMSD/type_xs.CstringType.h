#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CstringType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CstringType



namespace CMSD
{

namespace xs
{	

class CstringType : public TypeBase
{
public:
	CMSD_EXPORT CstringType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CstringType(CstringType const& init);
	void operator=(CstringType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_xs_altova_CstringType); }
	CMSD_EXPORT void operator=(const string_type& value);
	CMSD_EXPORT operator string_type();
	CMSD_EXPORT void SetXsiType();
};



} // namespace xs

}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CstringType
