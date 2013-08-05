#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CIdentifiableEntity
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CIdentifiableEntity

#include "type_.CEntity.h"


namespace CMSD
{

class CIdentifiableEntity : public ::CMSD::CEntity
{
public:
	CMSD_EXPORT CIdentifiableEntity(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CIdentifiableEntity(CIdentifiableEntity const& init);
	void operator=(CIdentifiableEntity const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CIdentifiableEntity); }
	MemberElement<xs::CstringType, _altova_mi_altova_CIdentifiableEntity_altova_Identifier> Identifier;
	struct Identifier { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CIdentifiableEntity_altova_Description> Description;
	struct Description { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<CReferenceMaterialReference, _altova_mi_altova_CIdentifiableEntity_altova_ReferenceMaterial> ReferenceMaterial;
	struct ReferenceMaterial { typedef Iterator<CReferenceMaterialReference> iterator; };
	MemberElement<CProperty, _altova_mi_altova_CIdentifiableEntity_altova_Property> Property;
	struct Property { typedef Iterator<CProperty> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CIdentifiableEntity
