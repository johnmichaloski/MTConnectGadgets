#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CArrayOfChoice1
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CArrayOfChoice1



namespace CMSD
{

class CArrayOfChoice1 : public TypeBase
{
public:
	CMSD_EXPORT CArrayOfChoice1(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CArrayOfChoice1(CArrayOfChoice1 const& init);
	void operator=(CArrayOfChoice1 const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CArrayOfChoice1); }
	MemberElement<CRotation, _altova_mi_altova_CArrayOfChoice1_altova_Rotation> Rotation;
	struct Rotation { typedef Iterator<CRotation> iterator; };
	MemberElement<CScaling, _altova_mi_altova_CArrayOfChoice1_altova_Scaling> Scaling;
	struct Scaling { typedef Iterator<CScaling> iterator; };
	MemberElement<CTranslation, _altova_mi_altova_CArrayOfChoice1_altova_Translation> Translation;
	struct Translation { typedef Iterator<CTranslation> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CArrayOfChoice1
