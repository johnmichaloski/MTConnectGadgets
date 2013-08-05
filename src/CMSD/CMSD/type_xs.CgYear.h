#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CgYear
#define _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CgYear



namespace CMSD
{

namespace xs
{	

class CgYear : public TypeBase
{
public:
	CMSD_EXPORT CgYear(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CgYear(CgYear const& init);
	void operator=(CgYear const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_CgYear); }
	void operator= (const altova::DateTime& value) 
	{
		altova::XmlFormatter* Formatter = static_cast<altova::XmlFormatter*>(altova::GYearFormatter);
		MsxmlTreeOperations::SetValue(GetNode(), Formatter->Format(value));
	}	
		
	operator altova::DateTime()
	{
		return CastAs<altova::DateTime >::Do(GetNode(), 0);
	}
};



} // namespace xs

}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CgYear
