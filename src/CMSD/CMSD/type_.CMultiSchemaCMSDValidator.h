#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CMultiSchemaCMSDValidator
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CMultiSchemaCMSDValidator



namespace CMSD
{

class CMultiSchemaCMSDValidator : public TypeBase
{
public:
	CMSD_EXPORT CMultiSchemaCMSDValidator(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CMultiSchemaCMSDValidator(CMultiSchemaCMSDValidator const& init);
	void operator=(CMultiSchemaCMSDValidator const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CMultiSchemaCMSDValidator); }
	MemberElement<xs::CbooleanType, _altova_mi_altova_CMultiSchemaCMSDValidator_altova_ValidateUsingSchematron> ValidateUsingSchematron;
	struct ValidateUsingSchematron { typedef Iterator<xs::CbooleanType> iterator; };
	MemberElement<xs::CbooleanType, _altova_mi_altova_CMultiSchemaCMSDValidator_altova_ValidateUsingRelaxNG> ValidateUsingRelaxNG;
	struct ValidateUsingRelaxNG { typedef Iterator<xs::CbooleanType> iterator; };
	MemberElement<xs::CbooleanType, _altova_mi_altova_CMultiSchemaCMSDValidator_altova_ValidateUsingXSD> ValidateUsingXSD;
	struct ValidateUsingXSD { typedef Iterator<xs::CbooleanType> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CMultiSchemaCMSDValidator
