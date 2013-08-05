#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CArrayOfTransformationOperation
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CArrayOfTransformationOperation



namespace CMSD
{

class CArrayOfTransformationOperation : public TypeBase
{
public:
	CMSD_EXPORT CArrayOfTransformationOperation(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CArrayOfTransformationOperation(CArrayOfTransformationOperation const& init);
	void operator=(CArrayOfTransformationOperation const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CArrayOfTransformationOperation); }
	MemberElement<CTransformationOperation, _altova_mi_altova_CArrayOfTransformationOperation_altova_TransformationOperation> TransformationOperation;
	struct TransformationOperation { typedef Iterator<CTransformationOperation> iterator; };
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CArrayOfTransformationOperation
