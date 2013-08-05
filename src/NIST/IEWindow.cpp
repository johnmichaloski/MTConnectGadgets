#include "StdAfx.h"
#include "IEWindow.h"
#include "StdStringFcn.h"

std::string CIEWindow::numberfields;

CIEWindow::CIEWindow(void)
{
	_nLive=1;
	_nSnapshot=-1;
}

CIEWindow::~CIEWindow(void)
{
}
void CIEWindow::LoadFields(std::string fields)
{
	_fields = Tokenize(fields,",");
	for(int i=0; i< _fields.size(); i++)
	{
		if(_fields[i].empty())
		{
			_fields.erase(_fields.begin() + i);
			i--;
		}
		Trim(_fields[i]);
	}

}

void __stdcall CIEWindow::OnBeforeNavigate(IDispatch *pDisp,VARIANT *URL,
										   VARIANT *Flags,VARIANT *TargetFrameName,VARIANT *PostData,VARIANT *Headers,
										   VARIANT_BOOL *Cancel)
{
	CString strURL(URL->bstrVal);
	CString strXML(strURL.Right(strURL.GetLength()-6));
	strXML.Replace("%20", " ");
	if(strURL.Find("back")>=0)
	{
		if(_nLive==1)
			_nSnapshot=_snapshots.size()-1;
		_nLive=0;

		_nSnapshot--;
		if(	_nSnapshot<0)
			_nSnapshot=0;

		SetSnapshot(_nSnapshot);

	}
	if(strURL.Find("fwd")>=0)
	{
		if(_nLive==1)
			_nSnapshot=_snapshots.size()-1;
		_nLive=0;

		_nSnapshot++;
		if(	_nSnapshot>=_snapshots.size())
			_nSnapshot=_snapshots.size()-1;

		SetSnapshot(_nSnapshot);
	}
	if(strURL.Find("run")>=0)
	{
		_nLive=1;
		SetSnapshot(-1);

	}
	*Cancel = TRUE;
}

int CIEWindow::SetSnapshot(int i)
{
	if(i == -1)
	{
		if(_nLive==1)
			SetElementId("Device", _snapshots[_snapshots.size()-1]);
		return _snapshots.size()-1;
	}
	if(i <0)
		i=0;
	if(i >=_snapshots.size())
		i=_snapshots.size()-1;
	if(i <0)
		return 0; // no data

	SetElementId("Device", _snapshots[i]);
	return i;
}
void CIEWindow::StoreSnapshot(std::string snapshot)
{
	// Don't save same snapshot
	if(_lastsnapshot==snapshot)
		return;
	_lastsnapshot=snapshot;
	_snapshots.push_back(snapshot); 
	if(_nLive==1)
		SetElementId("Device", snapshot);
}

bool CIEWindow::IsAlive()
{
	SHANDLE_PTR hwnd;
	if(m_spWebBrowser==NULL)
		return false;
	if(FAILED(m_spWebBrowser->get_HWND(&hwnd)))
		return false;
	if(hwnd==NULL)
		return false;

	return true;
}

HRESULT CIEWindow::SetWindowTitle(std::string s)
{
	if(m_spWebBrowser==NULL)
		OpenIE();

	if(m_spWebBrowser==NULL)
		return E_FAIL;

	return S_OK;

}


HRESULT CIEWindow::GetBody()
{
	HRESULT_EXCEPTION hr;
	CComPtr<IDispatch> pDisp;

	if(m_spWebBrowser==NULL)
		OpenIE();

	if(m_spWebBrowser==NULL)
		return E_FAIL;

	hr=m_spWebBrowser->get_Document( &pDisp);

	hr=pDisp->QueryInterface(IID_IHTMLDocument2, (void**)&m_spHTMLDocument);
	if(m_spHTMLDocument==NULL)
		return E_FAIL;

	//Handle NavigateComplete2 event from the browser, get the document  element, call DispEventAdvise(pDocument). onclick event bubbles, so you  can handle it on the document and get clicks from all contained  elements.
	//DispEventAdvise(m_spWebBrowser); 
	return S_OK;
}

CComPtr<IHTMLElement> CIEWindow::GetElement(const TCHAR *id)
{ 
	CComPtr<IHTMLElement> ret=0; 
	if (id==0) 
		return 0;

	IHTMLDocument2 *doc;
	if(m_spHTMLDocument==NULL)
		this->GetBody();

	doc= m_spHTMLDocument;
	if (doc==0) 
		return 0;

	CComPtr<IHTMLElementCollection> doc_all;
	HRESULT hr = doc->get_all(&doc_all);      // this is like doing document.all
	if (hr==S_OK)
	{ 
		VARIANT v0; VariantInit(&v0);

		CComPtr<IDispatch> disp;
		_variant_t vid((BSTR) _bstr_t(id));
		hr = doc_all->item(vid,v0,&disp);       // this is like doing document.all["messages"]
		if (hr==S_OK && disp!=0)
		{ 
			hr = disp->QueryInterface(IID_IHTMLElement,(void **)&ret); // it's the caller's responsibility to release ret
			if(FAILED(hr))
				return 0;
		}
	}
	return ret;
}

HRESULT CIEWindow::SetElementId(std::string id, std::string str)
{
	_bstr_t bstr(str.c_str());
	_bstr_t bid(id.c_str());

	IHTMLDocument2 *document;
	if(m_spHTMLDocument==NULL)
		this->GetBody();

	document= m_spHTMLDocument;
	CComPtr<IHTMLElement> elem = GetElement(id.c_str());
	if(elem==NULL)
		return E_FAIL;
	return	elem->put_innerHTML(bstr);
}
void CIEWindow::CloseIE()
{
	CComPtr<IWebBrowserApp> pBrowserApp=NULL;
	HWND hwnd;

	//m_spWebBrowser->QueryInterface(IID_IWebBrowserApp,(void **) &pBrowserApp);
	m_spWebBrowser->put_Visible(VARIANT_FALSE);
	m_spWebBrowser->get_HWND((SHANDLE_PTR *) &hwnd);
	pBrowserApp=NULL;
	m_spHTMLDocument=NULL;
	m_pBody=NULL;
	m_spWebBrowser->Quit();
	//::PostMessage(hwnd,WM_CLOSE, 0,0);
	m_spWebBrowser = NULL;
	//DestroyWindow(hwnd);

}
void CIEWindow::OpenIE()
{
	HRESULT_EXCEPTION hr;
	m_spWebBrowser = NULL; // Derived from IWebBrowser
	_bstr_t bstrURL, bstrHeaders;
	VARIANT vFlags = {0},
		vTargetFrameName = {0},
		vPostData = {0},
		vHeaders = {0};

	try
	{
		hr = CoCreateInstance(CLSID_InternetExplorer,
			NULL,
			CLSCTX_SERVER,
			IID_IWebBrowser2,
			(LPVOID*)&m_spWebBrowser);

		bstrURL = L"about:blank";

		hr = m_spWebBrowser->Navigate(bstrURL, &vFlags, &vTargetFrameName, &vPostData, &vHeaders);
		hr = m_spWebBrowser->put_Visible(VARIANT_TRUE);

	}
	catch(HRESULT hResult)
	{
		std::string errmsg =(LPCSTR)( "CIEWindow::OpenIE Failed: %s\n" +   ErrorFormatMessage(hResult));
		AtlTrace(errmsg.c_str());
		throw std::exception(errmsg.c_str());
	}
}

HRESULT CIEWindow::SetDocumentText(std::string cstr)
{
	_bstr_t tbstr(cstr.c_str());
	HRESULT_EXCEPTION hr = S_OK;
	VARIANT *param;
	SAFEARRAY *sfArray;
	IHTMLDocument2 *document;
	BSTR  bstr= tbstr.Detach();

	try
	{
		// Creates a new one-dimensional array
		sfArray = SafeArrayCreateVector(VT_VARIANT, 0, 1);

		if(m_spHTMLDocument==NULL)
			this->GetBody();

		document= m_spHTMLDocument;
		if (sfArray == NULL || document == NULL) 
			throw std::exception("CIEWindow::SetDocumentText) Failed IHTMLDocument2\n");

		hr = SafeArrayAccessData(sfArray,(LPVOID*) & param);
		param->vt = VT_BSTR;
		param->bstrVal = bstr;
		hr = SafeArrayUnaccessData(sfArray);
		hr = document->write(sfArray);
	}
	catch(std::exception e)
	{
		AtlTrace(e.what());
		throw e;
	}
	catch(HRESULT hResult)
	{
		std::string errmsg =(LPCSTR)( "CIEWindow::SetDocumentText Failed: %s\n" +   ErrorFormatMessage(hResult));
		AtlTrace("CIEWindow::SetDocumentText Failed: %s\n",  (LPCSTR) ErrorFormatMessage(hResult));
		throw std::exception(errmsg.c_str());
	}
	catch(...)
	{
		AtlTrace("CIEWindow::OpenIE() Failed\n");
		throw std::exception("CIEWindow::OpenIE() Failed\n");
	}

	if (sfArray != NULL) 
		SafeArrayDestroy(sfArray);
	return S_OK;
}


std::string  CIEWindow::CreateHtmlTable(std::vector<DataDictionary> datum)
{
	std::string htmltable;

	if(datum.size() < 1)
		return "";

	htmltable += "<TABLE>\n";
	htmltable +=   "<TR>";
	DataDictionary data = datum[0];
	for(int i=0; i< _fields.size(); i++)
	{

	htmltable +=   "<TH> " + _fields[i]  + "</TH> ";
	}
#if 0
	htmltable +=   "<TH> Timestamp</TH> ";
	for(DataDictionary::iterator it = data.begin(); it!=data.end(); it++)
	{
		std::string tag = ","+(*it).first+",";
		if(skip.find(tag) != std::string::npos)
			continue;
		htmltable +=   "<TH> " + (*it).first    + "</TH> ";
	}
#endif
	htmltable +=   "</TR>\n";

	for(int i=0; i< datum.size(); i++)
	{
		htmltable +=   "<TR>\n";
		htmltable +=CreateHtmlRow(datum[i]);
		htmltable +=   "</TR>\n";
	}

	htmltable += "</TABLE>\n";
	return htmltable;
}
std::string  CIEWindow::CreateHtmlRow(DataDictionary data)
{
	std::string htmltable;
	std::string style;
	double dVal=0.0;

	for(int i=0; i< _fields.size(); i++)
	{
		style.clear();
		std::string value = data[_fields[i]]; //(*it).second;
		std::string field = _fields[i]; //  (*it).first

		if(_valuerenames.find(field+"."+value)!=_valuerenames.end())
			value=_valuerenames[field+"."+value];

		if(_colormapping.find(field+"."+value)!=_colormapping.end())
			style =_colormapping[field+"."+value];


		if(field == "mode")
		{
			if(value == "MANUAL")  
			{
				style =   "style=\"background-color:yellow;\"";
			}
			if(value == "AUTOMATIC")  
			{
				style =    "style=\"background-color:#00FF33;\"";
			}	
		}
		if(field == "execution")
		{	
			if(value == "IDLE")  
			{
				style =   "style=\"background-color:lightblue;\"";
			}
			if(value == "EXECUTING")  
			{
				style =    "style=\"background-color:green;\"";
			}
			if(value == "STOPPED")  
				style =    "style=\"background-color:red;\"";
		}

		if(value == "UNAVAILABLE")
			value="<CENTER>--</CENTER>";
		if(numberfields.find(field) != std::string::npos && sscanf(value.c_str(),"%lf",&dVal))
		{
			value = StdStringFormat("%9.6f", dVal);
			style += " align=\"right\"";
		}
		if(_formats.find(field)!=_formats.end())
		{
			if(sscanf(value.c_str(),"%lf",&dVal))
			value = StdStringFormat(_formats[field].c_str(), dVal);
		}

		
		if(field == "Duration")
		{
			style = " align=\"right\"";
		}
		htmltable +=   "<TD " + style + "> "+ value + "</TD>" ;
	}

	return htmltable;
}