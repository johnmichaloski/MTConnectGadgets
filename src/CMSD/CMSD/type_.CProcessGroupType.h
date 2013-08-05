#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CProcessGroupType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CProcessGroupType



namespace CMSD
{

class CProcessGroupType : public TypeBase
{
public:
	CMSD_EXPORT CProcessGroupType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CProcessGroupType(CProcessGroupType const& init);
	void operator=(CProcessGroupType const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_altova_CProcessGroupType); }

	enum EnumValues {
		Invalid = -1,
		k_sequence = 0, // sequence
		k_concurrent = 1, // concurrent
		k_decision = 2, // decision
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

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CProcessGroupType
