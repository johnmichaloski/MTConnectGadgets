#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCMSDDocument
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCMSDDocument

#include "type_.CNotifyPropertyChangeBase.h"


namespace CMSD
{

class CCMSDDocument : public ::CMSD::CNotifyPropertyChangeBase
{
public:
	CMSD_EXPORT CCMSDDocument(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CCMSDDocument(CCMSDDocument const& init);
	void operator=(CCMSDDocument const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CCMSDDocument); }
	MemberElement<CHeaderSection, _altova_mi_altova_CCMSDDocument_altova_HeaderSection> HeaderSection;
	struct HeaderSection { typedef Iterator<CHeaderSection> iterator; };
	MemberElement<CDataSectionType2, _altova_mi_altova_CCMSDDocument_altova_DataSection> DataSection;
	struct DataSection { typedef Iterator<CDataSectionType2> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCMSDDocument
