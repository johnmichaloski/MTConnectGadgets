#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CInventoryItemTypeType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CInventoryItemTypeType



namespace CMSD
{

class CInventoryItemTypeType : public TypeBase
{
public:
	CMSD_EXPORT CInventoryItemTypeType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CInventoryItemTypeType(CInventoryItemTypeType const& init);
	void operator=(CInventoryItemTypeType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CInventoryItemTypeType); }

	enum EnumValues {
		Invalid = -1,
		k_part = 0, // part
		k_resource = 1, // resource
		EnumValueCount
	};

	
	CMSD_EXPORT int GetEnumerationValue();
	CMSD_EXPORT void SetEnumerationValue( const int index);
	CMSD_EXPORT void operator=(const string_type& value);
	CMSD_EXPORT operator string_type();
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CInventoryItemTypeType
