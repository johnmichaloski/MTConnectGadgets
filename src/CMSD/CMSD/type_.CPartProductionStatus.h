#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPartProductionStatus
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPartProductionStatus



namespace CMSD
{

class CPartProductionStatus : public TypeBase
{
public:
	CMSD_EXPORT CPartProductionStatus(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CPartProductionStatus(CPartProductionStatus const& init);
	void operator=(CPartProductionStatus const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_altova_CPartProductionStatus); }

	enum EnumValues {
		Invalid = -1,
		k_unknown = 0, // unknown
		k_workInProcess = 1, // workInProcess
		k_finishedGood = 2, // finishedGood
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

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPartProductionStatus
