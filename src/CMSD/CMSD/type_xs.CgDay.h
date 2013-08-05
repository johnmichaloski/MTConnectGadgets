#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CgDay
#define _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CgDay



namespace CMSD
{

namespace xs
{	

class CgDay : public TypeBase
{
public:
	CMSD_EXPORT CgDay(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CgDay(CgDay const& init);
	void operator=(CgDay const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_CgDay); }
	void operator= (const altova::DateTime& value) 
	{
		altova::XmlFormatter* Formatter = static_cast<altova::XmlFormatter*>(altova::GDayFormatter);
		MsxmlTreeOperations::SetValue(GetNode(), Formatter->Format(value));
	}	
		
	operator altova::DateTime()
	{
		return CastAs<altova::DateTime >::Do(GetNode(), 0);
	}
};



} // namespace xs

}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CgDay
