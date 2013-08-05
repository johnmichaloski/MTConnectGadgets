#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CReferenceProperty
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CReferenceProperty

#include "type_.CNotifyPropertyChangeBase.h"


namespace CMSD
{

class CReferenceProperty : public ::CMSD::CNotifyPropertyChangeBase
{
public:
	CMSD_EXPORT CReferenceProperty(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CReferenceProperty(CReferenceProperty const& init);
	void operator=(CReferenceProperty const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CReferenceProperty); }
	MemberElement<CAbstractEntityReference, _altova_mi_altova_CReferenceProperty_altova_AbstractEntityReference> AbstractEntityReference;
	struct AbstractEntityReference { typedef Iterator<CAbstractEntityReference> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CReferenceProperty
