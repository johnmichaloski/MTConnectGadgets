#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CLotInformation
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CLotInformation

#include "type_.CNotifyPropertyChangeBase.h"


namespace CMSD
{

class CLotInformation : public ::CMSD::CNotifyPropertyChangeBase
{
public:
	CMSD_EXPORT CLotInformation(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CLotInformation(CLotInformation const& init);
	void operator=(CLotInformation const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CLotInformation); }
	MemberElement<xs::CstringType, _altova_mi_altova_CLotInformation_altova_LotNumber> LotNumber;
	struct LotNumber { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CLotInformation_altova_ParentLotNumber> ParentLotNumber;
	struct ParentLotNumber { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CLotInformation_altova_Description> Description;
	struct Description { typedef Iterator<xs::CstringType> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CLotInformation
