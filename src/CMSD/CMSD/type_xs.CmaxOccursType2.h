#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CmaxOccursType2
#define _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CmaxOccursType2



namespace CMSD
{

namespace xs
{	

class CmaxOccursType2 : public TypeBase
{
public:
	CMSD_EXPORT CmaxOccursType2(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CmaxOccursType2(CmaxOccursType2 const& init);
	void operator=(CmaxOccursType2 const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_xs_altova_CmaxOccursType2); }

	enum EnumValues {
		Invalid = -1,
		k_0 = 0, // 0
		k_1 = 1, // 1
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

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CmaxOccursType2
