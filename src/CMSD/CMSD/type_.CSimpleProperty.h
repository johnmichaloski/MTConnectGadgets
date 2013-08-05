#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CSimpleProperty
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CSimpleProperty

#include "type_.CNotifyPropertyChangeBase.h"


namespace CMSD
{

class CSimpleProperty : public ::CMSD::CNotifyPropertyChangeBase
{
public:
	CMSD_EXPORT CSimpleProperty(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CSimpleProperty(CSimpleProperty const& init);
	void operator=(CSimpleProperty const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CSimpleProperty); }
	MemberElement<xs::CstringType, _altova_mi_altova_CSimpleProperty_altova_Value2> Value2;
	struct Value2 { typedef Iterator<xs::CstringType> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CSimpleProperty
