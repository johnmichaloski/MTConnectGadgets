#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CpatternType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CpatternType



namespace CMSD
{

class CpatternType : public TypeBase
{
public:
	CMSD_EXPORT CpatternType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CpatternType(CpatternType const& init);
	void operator=(CpatternType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CpatternType); }

	MemberAttribute<string_type,_altova_mi_altova_CpatternType_altova_id, 0, 0> id;	// id CID

	MemberAttribute<string_type,_altova_mi_altova_CpatternType_altova_value2, 0, 0> value2;	// value Cstring

	MemberAttribute<bool,_altova_mi_altova_CpatternType_altova_fixed, 0, 0> fixed;	// fixed Cboolean
	MemberElement<CannotationType, _altova_mi_altova_CpatternType_altova_annotation> annotation;
	struct annotation { typedef Iterator<CannotationType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CpatternType
