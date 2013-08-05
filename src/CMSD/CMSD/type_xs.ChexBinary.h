#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_ChexBinary
#define _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_ChexBinary



namespace CMSD
{

namespace xs
{	

class ChexBinary : public TypeBase
{
public:
	CMSD_EXPORT ChexBinary(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT ChexBinary(ChexBinary const& init);
	void operator=(ChexBinary const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_ChexBinary); }
	void operator= (const std::vector<unsigned char>& value) 
	{
		altova::XmlFormatter* Formatter = static_cast<altova::XmlFormatter*>(altova::HexBinaryFormatter);
		MsxmlTreeOperations::SetValue(GetNode(), Formatter->Format(value));
	}	
		
	operator std::vector<unsigned char>()
	{
		return CastAs<std::vector<unsigned char> >::Do(GetNode(), 0);
	}
};



} // namespace xs

}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_ChexBinary
