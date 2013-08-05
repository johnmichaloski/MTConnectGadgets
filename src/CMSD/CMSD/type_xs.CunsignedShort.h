#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CunsignedShort
#define _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CunsignedShort



namespace CMSD
{

namespace xs
{	

class CunsignedShort : public TypeBase
{
public:
	CMSD_EXPORT CunsignedShort(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CunsignedShort(CunsignedShort const& init);
	void operator=(CunsignedShort const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_CunsignedShort); }
	void operator= (const unsigned& value) 
	{
		altova::XmlFormatter* Formatter = static_cast<altova::XmlFormatter*>(altova::IntegerFormatter);
		MsxmlTreeOperations::SetValue(GetNode(), Formatter->Format(value));
	}	
		
	operator unsigned()
	{
		return CastAs<unsigned >::Do(GetNode(), 0);
	}
};



} // namespace xs

}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CunsignedShort
