#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CnonPositiveInteger
#define _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CnonPositiveInteger



namespace CMSD
{

namespace xs
{	

class CnonPositiveInteger : public TypeBase
{
public:
	CMSD_EXPORT CnonPositiveInteger(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CnonPositiveInteger(CnonPositiveInteger const& init);
	void operator=(CnonPositiveInteger const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_CnonPositiveInteger); }
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

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CnonPositiveInteger
