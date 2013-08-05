#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_Cboolean
#define _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_Cboolean



namespace CMSD
{

namespace xs
{	

class Cboolean : public TypeBase
{
public:
	CMSD_EXPORT Cboolean(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT Cboolean(Cboolean const& init);
	void operator=(Cboolean const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_Cboolean); }
	void operator= (const bool& value) 
	{
		altova::XmlFormatter* Formatter = static_cast<altova::XmlFormatter*>(altova::AnySimpleTypeFormatter);
		MsxmlTreeOperations::SetValue(GetNode(), Formatter->Format(value));
	}	
		
	operator bool()
	{
		return CastAs<bool >::Do(GetNode(), 0);
	}
};



} // namespace xs

}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_Cboolean
