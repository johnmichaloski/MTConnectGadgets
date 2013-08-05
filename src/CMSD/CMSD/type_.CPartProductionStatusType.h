#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPartProductionStatusType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPartProductionStatusType



namespace CMSD
{

class CPartProductionStatusType : public TypeBase
{
public:
	CMSD_EXPORT CPartProductionStatusType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CPartProductionStatusType(CPartProductionStatusType const& init);
	void operator=(CPartProductionStatusType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CPartProductionStatusType); }

	enum EnumValues {
		Invalid = -1,
		k_unknown = 0, // unknown
		k_workInProcess = 1, // workInProcess
		k_finishedGood = 2, // finishedGood
		EnumValueCount
	};

	
	CMSD_EXPORT int GetEnumerationValue();
	CMSD_EXPORT void SetEnumerationValue( const int index);
	CMSD_EXPORT void operator=(const string_type& value);
	CMSD_EXPORT operator string_type();
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPartProductionStatusType
