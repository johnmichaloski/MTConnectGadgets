#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CResourceGroupInformation
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CResourceGroupInformation

#include "type_.CNotifyPropertyChangeBase.h"


namespace CMSD
{

class CResourceGroupInformation : public ::CMSD::CNotifyPropertyChangeBase
{
public:
	CMSD_EXPORT CResourceGroupInformation(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CResourceGroupInformation(CResourceGroupInformation const& init);
	void operator=(CResourceGroupInformation const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CResourceGroupInformation); }
	MemberElement<CResourceGroupMember, _altova_mi_altova_CResourceGroupInformation_altova_ResourceGroupMember> ResourceGroupMember;
	struct ResourceGroupMember { typedef Iterator<CResourceGroupMember> iterator; };
	MemberElement<CConnection, _altova_mi_altova_CResourceGroupInformation_altova_Connection> Connection;
	struct Connection { typedef Iterator<CConnection> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CResourceGroupInformation
