#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CtotalDigitsType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CtotalDigitsType



namespace CMSD
{

class CtotalDigitsType : public TypeBase
{
public:
	CMSD_EXPORT CtotalDigitsType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CtotalDigitsType(CtotalDigitsType const& init);
	void operator=(CtotalDigitsType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CtotalDigitsType); }

	MemberAttribute<string_type,_altova_mi_altova_CtotalDigitsType_altova_id, 0, 0> id;	// id CID

	MemberAttribute<unsigned __int64,_altova_mi_altova_CtotalDigitsType_altova_value2, 0, 0> value2;	// value CpositiveInteger

	MemberAttribute<bool,_altova_mi_altova_CtotalDigitsType_altova_fixed, 0, 0> fixed;	// fixed Cboolean
	MemberElement<CannotationType, _altova_mi_altova_CtotalDigitsType_altova_annotation> annotation;
	struct annotation { typedef Iterator<CannotationType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CtotalDigitsType
