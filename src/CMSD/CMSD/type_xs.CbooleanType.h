#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CbooleanType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CbooleanType



namespace CMSD
{

namespace xs
{	

class CbooleanType : public TypeBase
{
public:
	CMSD_EXPORT CbooleanType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CbooleanType(CbooleanType const& init);
	void operator=(CbooleanType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_xs_altova_CbooleanType); }
	CMSD_EXPORT void operator=(const bool& value);
	CMSD_EXPORT operator bool();
	CMSD_EXPORT void SetXsiType();
};



} // namespace xs

}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CbooleanType
