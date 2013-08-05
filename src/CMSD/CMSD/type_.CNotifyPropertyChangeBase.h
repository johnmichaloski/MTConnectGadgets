#ifndef _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CNotifyPropertyChangeBase
#define _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CNotifyPropertyChangeBase



namespace CMSD
{

class CNotifyPropertyChangeBase : public TypeBase
{
public:
	CMSD_EXPORT CNotifyPropertyChangeBase(MSXML2::IXMLDOMNodePtr const& init);
	CMSD_EXPORT CNotifyPropertyChangeBase(CNotifyPropertyChangeBase const& init);
	void operator=(CNotifyPropertyChangeBase const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CNotifyPropertyChangeBase); }
	CMSD_EXPORT void SetXsiType();
};


}	// namespace CMSD

#endif // _ALTOVA_INCLUDED_CMSD_ALTOVA__ALTOVA_CNotifyPropertyChangeBase
