#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CLayoutObject
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CLayoutObject

#include "type_.CLayoutElement.h"


namespace CMSD
{

class CLayoutObject : public ::CMSD::CLayoutElement
{
public:
	CMSD_EXPORT CLayoutObject(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CLayoutObject(CLayoutObject const& init);
	void operator=(CLayoutObject const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CLayoutObject); }
	MemberElement<CResourceTypeType, _altova_mi_altova_CLayoutObject_altova_Type> Type;
	struct Type { typedef Iterator<CResourceTypeType> iterator; };
	MemberElement<CShapeDescription, _altova_mi_altova_CLayoutObject_altova_Shape> Shape;
	struct Shape { typedef Iterator<CShapeDescription> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CLayoutObject
