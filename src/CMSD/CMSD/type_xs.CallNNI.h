#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CallNNI
#define _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CallNNI



namespace CMSD
{

namespace xs
{	

class CallNNI : public TypeBase
{
public:
	CMSD_EXPORT CallNNI(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CallNNI(CallNNI const& init);
	void operator=(CallNNI const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_CallNNI); }

	enum EnumValues {
		Invalid = -1,
		k_unbounded = 0, // unbounded
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

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CallNNI
