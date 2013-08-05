#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_Cdecimal
#define _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_Cdecimal



namespace CMSD
{

namespace xs
{	

class Cdecimal : public TypeBase
{
public:
	CMSD_EXPORT Cdecimal(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT Cdecimal(Cdecimal const& init);
	void operator=(Cdecimal const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_Cdecimal); }
	void operator= (const double& value) 
	{
		altova::XmlFormatter* Formatter = static_cast<altova::XmlFormatter*>(altova::DecimalFormatter);
		MsxmlTreeOperations::SetValue(GetNode(), Formatter->Format(value));
	}	
		
	operator double()
	{
		return CastAs<double >::Do(GetNode(), 0);
	}
};



} // namespace xs

}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_Cdecimal
