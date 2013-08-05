#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CnonNegativeInteger
#define _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CnonNegativeInteger



namespace CMSD
{

namespace xs
{	

class CnonNegativeInteger : public TypeBase
{
public:
	CMSD_EXPORT CnonNegativeInteger(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CnonNegativeInteger(CnonNegativeInteger const& init);
	void operator=(CnonNegativeInteger const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_CnonNegativeInteger); }
	void operator= (const unsigned __int64& value) 
	{
		altova::XmlFormatter* Formatter = static_cast<altova::XmlFormatter*>(altova::IntegerFormatter);
		MsxmlTreeOperations::SetValue(GetNode(), Formatter->Format(value));
	}	
		
	operator unsigned __int64()
	{
		return CastAs<unsigned __int64 >::Do(GetNode(), 0);
	}
};



} // namespace xs

}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CnonNegativeInteger
