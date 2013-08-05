#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_Ctime
#define _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_Ctime



namespace CMSD
{

namespace xs
{	

class Ctime : public TypeBase
{
public:
	CMSD_EXPORT Ctime(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT Ctime(Ctime const& init);
	void operator=(Ctime const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_Ctime); }
	void operator= (const altova::DateTime& value) 
	{
		altova::XmlFormatter* Formatter = static_cast<altova::XmlFormatter*>(altova::TimeFormatter);
		MsxmlTreeOperations::SetValue(GetNode(), Formatter->Format(value));
	}	
		
	operator altova::DateTime()
	{
		return CastAs<altova::DateTime >::Do(GetNode(), 0);
	}
};



} // namespace xs

}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_Ctime
