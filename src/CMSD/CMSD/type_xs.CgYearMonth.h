#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CgYearMonth
#define _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CgYearMonth



namespace CMSD
{

namespace xs
{	

class CgYearMonth : public TypeBase
{
public:
	CMSD_EXPORT CgYearMonth(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CgYearMonth(CgYearMonth const& init);
	void operator=(CgYearMonth const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_CgYearMonth); }
	void operator= (const altova::DateTime& value) 
	{
		altova::XmlFormatter* Formatter = static_cast<altova::XmlFormatter*>(altova::GYearMonthFormatter);
		MsxmlTreeOperations::SetValue(GetNode(), Formatter->Format(value));
	}	
		
	operator altova::DateTime()
	{
		return CastAs<altova::DateTime >::Do(GetNode(), 0);
	}
};



} // namespace xs

}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CgYearMonth
