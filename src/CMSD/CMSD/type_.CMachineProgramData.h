#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CMachineProgramData
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CMachineProgramData

#include "type_.CNotifyPropertyChangeBase.h"


namespace CMSD
{

class CMachineProgramData : public ::CMSD::CNotifyPropertyChangeBase
{
public:
	CMSD_EXPORT CMachineProgramData(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CMachineProgramData(CMachineProgramData const& init);
	void operator=(CMachineProgramData const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CMachineProgramData); }
	MemberElement<xs::CstringType, _altova_mi_altova_CMachineProgramData_altova_MachineProgramName> MachineProgramName;
	struct MachineProgramName { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<CResourceReference, _altova_mi_altova_CMachineProgramData_altova_TargetMachine> TargetMachine;
	struct TargetMachine { typedef Iterator<CResourceReference> iterator; };
	MemberElement<CMachineProgramLocationType, _altova_mi_altova_CMachineProgramData_altova_MachineProgramLocation> MachineProgramLocation;
	struct MachineProgramLocation { typedef Iterator<CMachineProgramLocationType> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CMachineProgramData
