#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_Cdate
#define _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_Cdate



namespace CMSD
{

namespace xs
{	

class Cdate : public TypeBase
{
public:
	CMSD_EXPORT Cdate(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT Cdate(Cdate const& init);
	void operator=(Cdate const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_Cdate); }
	void operator= (const altova::DateTime& value) 
	{
		altova::XmlFormatter* Formatter = static_cast<altova::XmlFormatter*>(altova::DateFormatter);
		MsxmlTreeOperations::SetValue(GetNode(), Formatter->Format(value));
	}	
		
	operator altova::DateTime()
	{
		return CastAs<altova::DateTime >::Do(GetNode(), 0);
	}
};



} // namespace xs

}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_Cdate
