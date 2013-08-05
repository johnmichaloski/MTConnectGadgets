#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CwhiteSpaceType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CwhiteSpaceType



namespace CMSD
{

class CwhiteSpaceType : public TypeBase
{
public:
	CMSD_EXPORT CwhiteSpaceType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CwhiteSpaceType(CwhiteSpaceType const& init);
	void operator=(CwhiteSpaceType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CwhiteSpaceType); }

	MemberAttribute<string_type,_altova_mi_altova_CwhiteSpaceType_altova_id, 0, 0> id;	// id CID
	MemberAttribute<string_type,_altova_mi_altova_CwhiteSpaceType_altova_value2, 0, 3> value2;	// value CvalueType13

	MemberAttribute<bool,_altova_mi_altova_CwhiteSpaceType_altova_fixed, 0, 0> fixed;	// fixed Cboolean
	MemberElement<CannotationType, _altova_mi_altova_CwhiteSpaceType_altova_annotation> annotation;
	struct annotation { typedef Iterator<CannotationType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CwhiteSpaceType
