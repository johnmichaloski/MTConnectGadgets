#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CSegmentType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CSegmentType



namespace CMSD
{

class CSegmentType : public TypeBase
{
public:
	CMSD_EXPORT CSegmentType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CSegmentType(CSegmentType const& init);
	void operator=(CSegmentType const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_altova_CSegmentType); }

	enum EnumValues {
		Invalid = -1,
		k_straight = 0, // straight
		k_curved = 1, // curved
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


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CSegmentType
