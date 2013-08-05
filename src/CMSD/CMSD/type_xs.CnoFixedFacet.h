#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CnoFixedFacet
#define _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CnoFixedFacet



namespace CMSD
{

namespace xs
{	

class CnoFixedFacet : public TypeBase
{
public:
	CMSD_EXPORT CnoFixedFacet(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CnoFixedFacet(CnoFixedFacet const& init);
	void operator=(CnoFixedFacet const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_xs_altova_CnoFixedFacet); }

	MemberAttribute<string_type,_altova_mi_xs_altova_CnoFixedFacet_altova_id, 0, 0> id;	// id CID

	MemberAttribute<string_type,_altova_mi_xs_altova_CnoFixedFacet_altova_value2, 0, 0> value2;	// value CanySimpleType

	MemberAttribute<bool,_altova_mi_xs_altova_CnoFixedFacet_altova_fixed, 0, 0> fixed;	// fixed Cboolean
	MemberElement<CannotationType, _altova_mi_xs_altova_CnoFixedFacet_altova_annotation> annotation;
	struct annotation { typedef Iterator<CannotationType> iterator; };
	CMSD_EXPORT void SetXsiType();
};



} // namespace xs

}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CnoFixedFacet
