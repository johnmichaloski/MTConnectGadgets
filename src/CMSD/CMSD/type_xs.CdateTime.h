#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CdateTime
#define _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CdateTime



namespace CMSD
{

namespace xs
{	

class CdateTime : public TypeBase
{
public:
	CMSD_EXPORT CdateTime(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CdateTime(CdateTime const& init);
	void operator=(CdateTime const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_CdateTime); }
	void operator= (const altova::DateTime& value) 
	{
		altova::XmlFormatter* Formatter = static_cast<altova::XmlFormatter*>(altova::DateTimeFormatter);
		MsxmlTreeOperations::SetValue(GetNode(), Formatter->Format(value));
	}	
		
	operator altova::DateTime()
	{
		return CastAs<altova::DateTime >::Do(GetNode(), 0);
	}
};



} // namespace xs

}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CdateTime
