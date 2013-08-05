#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_Clong
#define _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_Clong



namespace CMSD
{

namespace xs
{	

class Clong : public TypeBase
{
public:
	CMSD_EXPORT Clong(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT Clong(Clong const& init);
	void operator=(Clong const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_Clong); }
	void operator= (const __int64& value) 
	{
		altova::XmlFormatter* Formatter = static_cast<altova::XmlFormatter*>(altova::IntegerFormatter);
		MsxmlTreeOperations::SetValue(GetNode(), Formatter->Format(value));
	}	
		
	operator __int64()
	{
		return CastAs<__int64 >::Do(GetNode(), 0);
	}
};



} // namespace xs

}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_Clong
