#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCMSDDocumentReference
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCMSDDocumentReference

#include "type_.CNotifyPropertyChangeBase.h"


namespace CMSD
{

class CCMSDDocumentReference : public ::CMSD::CNotifyPropertyChangeBase
{
public:
	CMSD_EXPORT CCMSDDocumentReference(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CCMSDDocumentReference(CCMSDDocumentReference const& init);
	void operator=(CCMSDDocumentReference const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CCMSDDocumentReference); }
	MemberElement<xs::CstringType, _altova_mi_altova_CCMSDDocumentReference_altova_LocalDocumentIdentifier> LocalDocumentIdentifier;
	struct LocalDocumentIdentifier { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<CDocumentLocationType, _altova_mi_altova_CCMSDDocumentReference_altova_DocumentLocation> DocumentLocation;
	struct DocumentLocation { typedef Iterator<CDocumentLocationType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CCMSDDocumentReference_altova_Description> Description;
	struct Description { typedef Iterator<xs::CstringType> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CCMSDDocumentReference
