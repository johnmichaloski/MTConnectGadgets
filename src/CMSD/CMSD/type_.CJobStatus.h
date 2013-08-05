#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CJobStatus
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CJobStatus



namespace CMSD
{

class CJobStatus : public TypeBase
{
public:
	CMSD_EXPORT CJobStatus(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CJobStatus(CJobStatus const& init);
	void operator=(CJobStatus const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_altova_CJobStatus); }

	enum EnumValues {
		Invalid = -1,
		k_released = 0, // released
		k_started = 1, // started
		k_unknown = 2, // unknown
		k_completed = 3, // completed
		k_cancelled = 4, // cancelled
		k_blocked = 5, // blocked
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

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CJobStatus
