#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_Cfloat
#define _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_Cfloat



namespace CMSD
{

namespace xs
{	

class Cfloat : public TypeBase
{
public:
	CMSD_EXPORT Cfloat(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT Cfloat(Cfloat const& init);
	void operator=(Cfloat const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_Cfloat); }
	void operator= (const double& value) 
	{
		altova::XmlFormatter* Formatter = static_cast<altova::XmlFormatter*>(altova::DoubleFormatter);
		MsxmlTreeOperations::SetValue(GetNode(), Formatter->Format(value));
	}	
		
	operator double()
	{
		return CastAs<double >::Do(GetNode(), 0);
	}
};



} // namespace xs

}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_Cfloat
