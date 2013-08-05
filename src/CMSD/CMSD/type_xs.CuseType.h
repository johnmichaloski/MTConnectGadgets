#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CuseType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CuseType



namespace CMSD
{

namespace xs
{	

class CuseType : public TypeBase
{
public:
	CMSD_EXPORT CuseType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CuseType(CuseType const& init);
	void operator=(CuseType const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_CuseType); }

	enum EnumValues {
		Invalid = -1,
		k_prohibited = 0, // prohibited
		k_optional = 1, // optional
		k_required = 2, // required
		EnumValueCount
	};
	void operator= (const string_type& value) 
	{
		altova::XmlFormatter* Formatter = static_cast<altova::XmlFormatter*>(altova::AnySimpleTypeFormatter);
		MsxmlTreeOperations::SetValue(GetNode(), Formatter->Format(value));
	}	
		
	operator string_type()
	{
		return CastAs<string_type >::Do(GetNode(), 0);
	}
};



} // namespace xs

}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CuseType
