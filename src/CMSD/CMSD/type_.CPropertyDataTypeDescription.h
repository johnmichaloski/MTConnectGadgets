#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPropertyDataTypeDescription
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPropertyDataTypeDescription

#include "type_.CNotifyPropertyChangeBase.h"


namespace CMSD
{

class CPropertyDataTypeDescription : public ::CMSD::CNotifyPropertyChangeBase
{
public:
	CMSD_EXPORT CPropertyDataTypeDescription(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CPropertyDataTypeDescription(CPropertyDataTypeDescription const& init);
	void operator=(CPropertyDataTypeDescription const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CPropertyDataTypeDescription); }
	MemberElement<CPropertyTypeType, _altova_mi_altova_CPropertyDataTypeDescription_altova_PropertyDataType> PropertyDataType;
	struct PropertyDataType { typedef Iterator<CPropertyTypeType> iterator; };
	MemberElement<CReferenceTypeNameType, _altova_mi_altova_CPropertyDataTypeDescription_altova_ReferenceType> ReferenceType;
	struct ReferenceType { typedef Iterator<CReferenceTypeNameType> iterator; };
	MemberElement<CSimpleDataTypeNameType, _altova_mi_altova_CPropertyDataTypeDescription_altova_SimpleValueDataType> SimpleValueDataType;
	struct SimpleValueDataType { typedef Iterator<CSimpleDataTypeNameType> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CPropertyDataTypeDescription
