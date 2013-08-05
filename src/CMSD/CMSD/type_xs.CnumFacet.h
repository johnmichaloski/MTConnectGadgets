#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CnumFacet
#define _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CnumFacet



namespace CMSD
{

namespace xs
{	

class CnumFacet : public TypeBase
{
public:
	CMSD_EXPORT CnumFacet(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CnumFacet(CnumFacet const& init);
	void operator=(CnumFacet const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_xs_altova_CnumFacet); }

	MemberAttribute<string_type,_altova_mi_xs_altova_CnumFacet_altova_id, 0, 0> id;	// id CID

	MemberAttribute<unsigned __int64,_altova_mi_xs_altova_CnumFacet_altova_value2, 0, 0> value2;	// value CnonNegativeInteger

	MemberAttribute<bool,_altova_mi_xs_altova_CnumFacet_altova_fixed, 0, 0> fixed;	// fixed Cboolean
	MemberElement<CannotationType, _altova_mi_xs_altova_CnumFacet_altova_annotation> annotation;
	struct annotation { typedef Iterator<CannotationType> iterator; };
	CMSD_EXPORT void SetXsiType();
};



} // namespace xs

}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA_xs_ALTOVA_CnumFacet
