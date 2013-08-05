#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CHoliday
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CHoliday

#include "type_.CLimitedUniqueEntity.h"


namespace CMSD
{

class CHoliday : public ::CMSD::CLimitedUniqueEntity
{
public:
	CMSD_EXPORT CHoliday(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CHoliday(CHoliday const& init);
	void operator=(CHoliday const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CHoliday); }
	MemberElement<CDateType2, _altova_mi_altova_CHoliday_altova_Date> Date;
	struct Date { typedef Iterator<CDateType2> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CHoliday
