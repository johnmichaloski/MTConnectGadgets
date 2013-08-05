#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CAvailabilityException
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CAvailabilityException

#include "type_.CNotifyPropertyChangeBase.h"


namespace CMSD
{

class CAvailabilityException : public ::CMSD::CNotifyPropertyChangeBase
{
public:
	CMSD_EXPORT CAvailabilityException(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CAvailabilityException(CAvailabilityException const& init);
	void operator=(CAvailabilityException const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CAvailabilityException); }
	MemberElement<CExceptionDateType, _altova_mi_altova_CAvailabilityException_altova_ExceptionDate> ExceptionDate;
	struct ExceptionDate { typedef Iterator<CExceptionDateType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CAvailabilityException_altova_Description> Description;
	struct Description { typedef Iterator<xs::CstringType> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CAvailabilityException
