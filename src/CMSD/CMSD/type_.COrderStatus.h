#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_COrderStatus
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_COrderStatus



namespace CMSD
{

class COrderStatus : public TypeBase
{
public:
	CMSD_EXPORT COrderStatus(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT COrderStatus(COrderStatus const& init);
	void operator=(COrderStatus const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_altova_COrderStatus); }

	enum EnumValues {
		Invalid = -1,
		k_unknown = 0, // unknown
		k_created = 1, // created
		k_released = 2, // released
		k_completed = 3, // completed
		k_shipped = 4, // shipped
		k_cancelled = 5, // cancelled
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

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_COrderStatus
