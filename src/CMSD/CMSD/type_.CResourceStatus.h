#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CResourceStatus
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CResourceStatus



namespace CMSD
{

class CResourceStatus : public TypeBase
{
public:
	CMSD_EXPORT CResourceStatus(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CResourceStatus(CResourceStatus const& init);
	void operator=(CResourceStatus const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_altova_CResourceStatus); }

	enum EnumValues {
		Invalid = -1,
		k_busy = 0, // busy
		k_idle = 1, // idle
		k_broken = 2, // broken
		k_underMaintenance = 3, // underMaintenance
		k_unknown = 4, // unknown
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

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CResourceStatus
