#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CMachineProgramLocationType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CMachineProgramLocationType



namespace CMSD
{

class CMachineProgramLocationType : public TypeBase
{
public:
	CMSD_EXPORT CMachineProgramLocationType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CMachineProgramLocationType(CMachineProgramLocationType const& init);
	void operator=(CMachineProgramLocationType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CMachineProgramLocationType); }
	MemberElement<CschemaType, _altova_mi_altova_CMachineProgramLocationType_altova_schema> schema;
	struct schema { typedef Iterator<CschemaType> iterator; };
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CMachineProgramLocationType
