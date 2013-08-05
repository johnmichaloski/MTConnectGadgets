#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CopenAttrs
#define _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CopenAttrs



namespace CMSD
{

namespace xs
{	

class CopenAttrs : public TypeBase
{
public:
	CMSD_EXPORT CopenAttrs(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CopenAttrs(CopenAttrs const& init);
	void operator=(CopenAttrs const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_xs_altova_CopenAttrs); }
	CMSD_EXPORT void SetXsiType();
};



} // namespace xs

}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CopenAttrs
