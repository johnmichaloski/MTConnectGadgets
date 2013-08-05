#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CArrayOfChoice2
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CArrayOfChoice2



namespace CMSD
{

class CArrayOfChoice2 : public TypeBase
{
public:
	CMSD_EXPORT CArrayOfChoice2(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CArrayOfChoice2(CArrayOfChoice2 const& init);
	void operator=(CArrayOfChoice2 const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CArrayOfChoice2); }
	MemberElement<CRotation, _altova_mi_altova_CArrayOfChoice2_altova_Rotation> Rotation;
	struct Rotation { typedef Iterator<CRotation> iterator; };
	MemberElement<CScaling, _altova_mi_altova_CArrayOfChoice2_altova_Scaling> Scaling;
	struct Scaling { typedef Iterator<CScaling> iterator; };
	MemberElement<CTranslation, _altova_mi_altova_CArrayOfChoice2_altova_Translation> Translation;
	struct Translation { typedef Iterator<CTranslation> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CArrayOfChoice2
