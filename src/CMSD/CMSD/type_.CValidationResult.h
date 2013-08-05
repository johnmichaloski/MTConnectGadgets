#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CValidationResult
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CValidationResult



namespace CMSD
{

class CValidationResult : public TypeBase
{
public:
	CMSD_EXPORT CValidationResult(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CValidationResult(CValidationResult const& init);
	void operator=(CValidationResult const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CValidationResult); }
	MemberElement<xs::CstringType, _altova_mi_altova_CValidationResult_altova_ErrorMessage> ErrorMessage;
	struct ErrorMessage { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CbooleanType, _altova_mi_altova_CValidationResult_altova_Valid> Valid;
	struct Valid { typedef Iterator<xs::CbooleanType> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CValidationResult
