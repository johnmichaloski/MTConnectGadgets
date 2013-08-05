#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CdocumentationType
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CdocumentationType



namespace CMSD
{

class CdocumentationType : public TypeBase
{
public:
	CMSD_EXPORT CdocumentationType(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CdocumentationType(CdocumentationType const& init);
	void operator=(CdocumentationType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CdocumentationType); }
	CMSD_EXPORT void operator=(const string_type& value);
	CMSD_EXPORT operator string_type();

	MemberAttribute<string_type,_altova_mi_altova_CdocumentationType_altova_source, 0, 0> source;	// source CanyURI
	MemberAttribute<string_type,_altova_mi_altova_CdocumentationType_altova_lang, 0, 1> lang;	// lang ClangType
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CdocumentationType
