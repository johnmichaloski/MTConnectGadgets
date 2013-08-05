//
// Snapshots.cpp
//
// DISCLAIMER:
// This software was developed by U.S. Government employees as part of
// their official duties and is not subject to copyright. No warranty implied 
// or intended.

#include "StdAfx.h"
#include <tlhelp32.h>
#include "Snapshots.h"
#include "StdStringFcn.h"
#include "MtConnectDboard.h"
#include "Logger.h"
#include "DBLogger.h"

extern CComPtr<IGlobalInterfaceTable> pGIT;


#define TESTHR(X) \
	if(FAILED(hr=X))\
{ std::string errmsg=StdStringFormat("%s:%s%s",__FILE__ ,__LINE__ ,#X) ;\
	errmsg+=ErrorFormatMessage(hr);\
	throw std::exception(errmsg.c_str());\
}


static void trans_func( unsigned int u, EXCEPTION_POINTERS* pExp )
{
	std::string errmsg = StdStringFormat("Fanuc Shdr trans_func - Code = 0x%x\n",  
		pExp->ExceptionRecord->ExceptionCode) ;

	GLogger << FATAL << "FanucMTConnectAdapter::gatherDeviceData Exception Raised\n" << errmsg << std::endl;
	throw std::exception(errmsg.c_str());
}

static int GetShiftTime(std::string s)
{
	int Hour, Minute;
	if(sscanf(s.c_str(), "%d:%d", &Hour, &Minute)==2){}
	else return 0;//throw std::exception("Bad Shift time format -  hh:mm\n");
	return Hour * 60 + Minute;

}
void KillProgram(std::string progname)
{
	GLogger << INFO << "KillProgram" << std::endl; 
	HANDLE hProcessSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0 );

	// Initialize the process entry structure.
	PROCESSENTRY32 ProcessEntry = { 0 };
	ProcessEntry.dwSize = sizeof( ProcessEntry );

	// Get the first process info.
	if(! Process32First( hProcessSnapShot,&ProcessEntry ))
		return;

	do
	{
		if (_tcsicmp(ProcessEntry.szExeFile, progname.c_str()) ==0) 
		{ 
			HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, ProcessEntry.th32ProcessID); //Open Process to terminate
			GLogger << FATAL << "TerminateProcess: " << progname << std::endl; 
			TerminateProcess(hProcess,0);
			CloseHandle(hProcess); //Close Handle 
			return;

		}
	}
	while( Process32Next( hProcessSnapShot, &ProcessEntry ));

	// Close the handle
	CloseHandle( hProcessSnapShot );

}

void __stdcall CHtmlTableSnapshots::OnReset(BSTR items)
{
	::MessageBox(NULL, "Hello World","", MB_OK);
}
	  
	  ///////////////////////////////////////////////////////////////////////////////

CHtmlTableSnapshots::CHtmlTableSnapshots() 
{
	_nSnapshot=-1;
	_sShift="<BR><H3>Shift 1</H3>";
	pTrayIcon=NULL;
	_loggedon=true;
	shiftbusytime=0;
}
void CHtmlTableSnapshots::Logoff()
{
	GLogger << FATAL << "CHtmlTableSnapshots::Logoff()" << std::endl; 
	_loggedon=false;
	Disconnect();
}

void CHtmlTableSnapshots::Clear()
{
	datum.clear();
	_alarmHandler.Clear(); 
	shifttimer.restart();
	shiftbusytime=0;

	try {
	if(pTrayIcon != NULL)
		pTrayIcon->Clear();
	}
	catch(...){}
}

void CHtmlTableSnapshots::Logon()
{
	GLogger << FATAL << "CHtmlTableSnapshots::Logon()" << std::endl; 
	_loggedon=true;
}
void CHtmlTableSnapshots::Shutdown()
{
	_mRunning=false;
	GLogger << FATAL << "CHtmlTableSnapshots::Shutdown()" << std::endl; 
	_loggedon=false;
}

void CHtmlTableSnapshots::Disconnect()
{
	GLogger << FATAL << "CHtmlTableSnapshots::Disconnect()" << std::endl; 
	DispEventUnadvise(pTrayIcon);
	pTrayIcon=NULL; 
	_lasttooltip.clear();
	_sLastShift.clear();

}
CComPtr<IWebBrowser2> CHtmlTableSnapshots::GetWebBrowser()
{
	HRESULT hr=S_OK;
	CComPtr<IWebBrowser2> pWebBrowser=NULL;
	CComPtr<IUnknown> pUnk;

	try {
		GLogger << INFO << "CHtmlTableSnapshots::GetWebBrowser Logged on: " << _loggedon << std::endl; 
		if(!_loggedon)
		{
			pTrayIcon=NULL; // release  tray icon
			return NULL;
		}
		if(pTrayIcon==NULL  && _loggedon)
		{
			// Restart GUI COM server
			//KillProgram("MtConnectDboardGui.exe");
			// transition
			//::Sleep(3000);
		}
		if(pTrayIcon==NULL )
		{
			GLogger << INFO << "GetWebBrowser TrayIcon Null" << std::endl; 
			if(FAILED(hr=CoCreateInstance(__uuidof(MtConnectDboardGuiLib::CMTConnectTrayIcon), //clsid,
				NULL,
				CLSCTX_LOCAL_SERVER,
				__uuidof(	MtConnectDboardGuiLib::ICMTConnectTrayIcon),
				(void**)&pTrayIcon 
				)))
			{
				Disconnect();
				GLogger << FATAL << "CoCreateInstance MtConnectDboardGuiLib::CMTConnectTrayIcon failed"<<ErrorFormatMessage(hr)<<std::endl; 
				return NULL;
			}
			TESTHR(DispEventAdvise(pTrayIcon));
			TESTHR(pTrayIcon->CreateTabWindow(_bstr_t(this->_sMachine.c_str())));
			TESTHR(pTrayIcon->SetHeaderColumns(_bstr_t(_headers.c_str())));
			TESTHR(pTrayIcon->SetIpAddr(bstr_t(MTConnectStreamsParser::GetMTConnectUrl(_ipaddr).c_str())));
			TESTHR(pTrayIcon->Types(bstr_t(String(_typedatum.Keys()).c_str()),
				bstr_t( String(_typedatum.ValueList(_typedatum.Keys())).c_str())
				));
			TESTHR(pTrayIcon->Formats(bstr_t(String(_formats.Keys()).c_str()),
				bstr_t(String( _formats.ValueList(_formats.Keys())).c_str())
				));

			TESTHR(pTrayIcon->SetFaultColumns(_bstr_t("Severity,RaisedBy,Description,Program,RaisedAt,ResolvedAt,TBF,TTR")));


		}
		TESTHR(pTrayIcon->raw_GetPointerBrowser(&pUnk));
		TESTHR(pUnk->QueryInterface(__uuidof(IWebBrowser2), (void **) &pWebBrowser));
		return pWebBrowser;	
	}
	catch(_com_error)
	{
		Disconnect();
		pWebBrowser=NULL;

	}
	catch(std::exception errmsg)
	{
		Disconnect();
		GLogger << INFO << "CHtmlTableSnapshots::GetWebBrowser() exception" << errmsg.what() << std::endl;
		pWebBrowser=NULL;

	}	
	catch(...)
	{
		Disconnect();
		GLogger << INFO << "CHtmlTableSnapshots::GetWebBrowser() ... exception" << std::endl;
		pWebBrowser=NULL;
	}
	return pWebBrowser;
}
void CHtmlTableSnapshots::SetState(StateDef state) 
{ 
	_state=state; 
}
void CHtmlTableSnapshots::Update()
{
	static int cnt=0;
	HRESULT hr=S_OK;
	try{
		CComPtr<IWebBrowser2> pWebBrowser = GetWebBrowser();
		//if(++cnt % 100)
		//{
		//	GLogger << INFO << "CHtmlTableSnapshots::Update " << std::endl; 
		//	//SHANDLE_PTR  pHWND;
		//	/*
		//	if you are trying to get a HWND handle of a WebBrowser
		//	control hosted in a window other than Internet Explorer
		//	you should use the IOleWindow::GetWindow() instead.
		//	IWebBrowser2::get_HWND() only works for IE hosted WebBrowser controls.
		//	=:o
		//	*/
		//	// pWebBrowser->get_HWND(&pHWND);
		//	//GLogger << INFO << "GetWebBrowser Visible " << (LONG) pHWND << std::endl; 
		//}
		if(pWebBrowser==NULL)
			return;

		// Handle table
		if(pWebBrowser!=NULL  && _lastsnapshot!=_snapshot)
		{
			SetElementId(pWebBrowser, "Device", _snapshot);
			TESTHR(pTrayIcon->AddRow(bstr_t(ToString(_headers).c_str()),
				_bstr_t(datum[0].ValueString(_headers).c_str())));

		}


		_lastsnapshot=_snapshot;

		if(pWebBrowser!=NULL  &&  _tooltip!=_lasttooltip)
			pTrayIcon->SetTooltip(_bstr_t(_tooltip.c_str()));

		_lasttooltip=_tooltip;
		if(_sShift!=_sLastShift && pWebBrowser!=NULL)
			SetElementId(pWebBrowser, "Header", _sShift);
		_sLastShift=_sShift;

		if(_state==CHtmlTableSnapshots::AUTO_RUNNING && pTrayIcon != NULL)
			pTrayIcon->SetTrayIconColor(_bstr_t("GREEN"), VARIANT_TRUE);
		else if(_state==CHtmlTableSnapshots::AUTO_IDLE && pTrayIcon != NULL)
			pTrayIcon->SetTrayIconColor(_bstr_t("GREEN"), VARIANT_FALSE);
		else if(_state==CHtmlTableSnapshots::MANUAL && pTrayIcon != NULL)
			pTrayIcon->SetTrayIconColor(_bstr_t("BLUE"), VARIANT_FALSE);
		else if(_state==CHtmlTableSnapshots::FAULT && pTrayIcon != NULL )
			pTrayIcon->SetTrayIconColor(_bstr_t("RED"), VARIANT_TRUE);
		else if(_state==CHtmlTableSnapshots::STOPPED && pTrayIcon != NULL)
			pTrayIcon->SetTrayIconColor(_bstr_t("RED"), VARIANT_FALSE);

		while(_alarmHandler._allfaultdatum.size() > 0)
		{
			std::string values = _alarmHandler._allfaultdatum.back().ValueString(_alarmHandler._faultitems);
			_alarmHandler._allfaultdatum.pop_back();
			pTrayIcon->AddFaultRow(bstr_t(ToString(_alarmHandler._faultitems).c_str()),
				bstr_t(values.c_str()));
			
			//std::string dbvalues = _alarmHandler._allfaultdatum.back().ValueString(_alarmHandler._faultitems);

			odbc.insert("Factory","Alarms",
				TrimmedTokenize(_alarmHandler._faultitems,","),
				TrimmedTokenize(values,","), 
				_typedatum);
		}
	}
	catch(std::exception errmsg)
	{
		Disconnect();
		GLogger << INFO << "CHtmlTableSnapshots::Update()" << errmsg.what() << std::endl;

	}	
	catch(...)
	{
		Disconnect();
	}
}
void CHtmlTableSnapshots::StoreSnapshot(std::string snapshot)
{
	_snapshot=snapshot; 
}

void CHtmlTableSnapshots::StoreShift(int shift)
{
	_sShift="<H1>Status of " + _sMachine + StdStringFormat(" - Shift %d", shift) + "</H1>";
}
CComPtr<IHTMLDocument2> CHtmlTableSnapshots::GetDocument(CComPtr<IWebBrowser2> pWebBrowser)
{
	HRESULT_EXCEPTION hr;
	CComPtr<IDispatch> pDisp;
	CComPtr<IHTMLDocument2> pHTMLDocument;
	if(pWebBrowser==NULL)
		return NULL; // throw std::exception("CMainDlg::GetDocument() pWebBrowser NULL\n");

	try{

		hr=pWebBrowser->get_Document( &pDisp);

		hr=pDisp->QueryInterface(IID_IHTMLDocument2, (void**)&pHTMLDocument);
		if(pHTMLDocument==NULL )
			throw std::exception("CMainDlg::GetDocument() pHTMLDocument NULL\n");

	}	
	catch(...)
	{
		Disconnect();
		return NULL;
	}
	return pHTMLDocument;
}
CComPtr<IHTMLElement> CHtmlTableSnapshots::GetElement(CComPtr<IWebBrowser2> pWebBrowser, const TCHAR *id)
{ 
	CComPtr<IHTMLElement> ret(NULL); 
	if (id==0) 
		return 0;

	try {
		CComPtr<IHTMLDocument2>  doc	= this->GetDocument(pWebBrowser);
		if (doc==0) 
			return NULL;

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
					throw HRESULT(hr);
			}
		}
	}	
	catch(...)
	{
		Disconnect();
		return NULL;
	}
	return ret;
}
HRESULT CHtmlTableSnapshots::SetElementId(CComPtr<IWebBrowser2> pWebBrowser, std::string id, std::string str)
{
	_bstr_t bstr(str.c_str());
	_bstr_t bid(id.c_str());
	HRESULT hr;
	try{
		CComPtr<IHTMLElement> elem = GetElement(pWebBrowser, id.c_str());
		if(elem==NULL)
			return E_FAIL;
		hr=	elem->put_innerHTML(bstr);
	}
	catch(...)
	{
		Disconnect();
		return E_FAIL;
	}
	return hr;
}
HRESULT CHtmlTableSnapshots::SetDocumentText(std::string cstr)
{
	_bstr_t tbstr(cstr.c_str());
	HRESULT_EXCEPTION hr = S_OK;
	HRESULT hres=S_OK;
	VARIANT *param;
	SAFEARRAY *sfArray;
	CComPtr<IHTMLDocument2> document;
	BSTR  bstr= tbstr.Detach();

	try
	{
		CComPtr<IWebBrowser2> pWebBrowser = GetWebBrowser();
		if(pWebBrowser==NULL)
			throw std::exception("CMainDlg::GetDocument() pWebBrowser NULL\n");

		// Creates a new one-dimensional array
		sfArray = SafeArrayCreateVector(VT_VARIANT, 0, 1);

		document=GetDocument(pWebBrowser);
		if (sfArray == NULL || document == NULL) 
			throw std::exception("CMainDlg::SetDocumentText) Failed IHTMLDocument2\n");

		hr = SafeArrayAccessData(sfArray,(LPVOID*) & param);
		param->vt = VT_BSTR;
		param->bstrVal = bstr;
		hr = SafeArrayUnaccessData(sfArray);
		hr = document->write(sfArray);
	}
	catch(std::exception e)
	{
		AtlTrace(e.what());
		Disconnect();
		hres= E_FAIL;
	}
	catch(HRESULT hResult)
	{
		std::string errmsg =(LPCSTR)( "CMainDlg::SetDocumentText Failed: %s\n" +   ErrorFormatMessage(hResult));
		AtlTrace("CMainDlg::SetDocumentText Failed: %s\n",  (LPCSTR) ErrorFormatMessage(hResult));
		Disconnect();
		hres= E_FAIL;
	}
	catch(...)
	{
		AtlTrace("CMainDlg::OpenIE() Failed\n");
		Disconnect();
		hres= E_FAIL;
	}

	if (sfArray != NULL) 
		SafeArrayDestroy(sfArray);
	return hres;
}
void CHtmlTableSnapshots::Configure(crp::Config &config,
		std::string sMachine, // machine name
		std::string ipaddr, // ip address of agent
		std::string configname // section name to lookup configuration info
		)
{
	_sMachine= sMachine;
	_ipaddr= ipaddr;
	_delay =  config.GetSymbolValue("CONFIG.DELAY", L"2500").toNumber<int>();

	_colormapping =  config.getmap("COLORCODING");
	_formats =  config.getmap("FORMATS");

	_numberfields =  config.GetSymbolValue("CONFIG.Numbers", L"").c_str();
	_numberfields+=",Shift";
	_dateTimefields =  config.GetSymbolValue("CONFIG.DateTime", L"").c_str();
	_KPIList = config.GetTokens("CONFIG.KPI", ",");
	_fields = config.GetTokens("CONFIG.Fields", ","); 
	_dbeventfields = config.GetTokens("CONFIG.DbEventFields", ","); 

	//???
	_headers= config.GetSymbolValue("CONFIG.SummaryHeader", L"").c_str();
	//_sHeader =  config.GetSymbolValue("CONFIG.Header", L"MTConnect Readings").c_str();

	_typedatum.Mixin(MTConnectStreamsParser::_saveddata, "adVarWChar");
	_typedatum.Mixin(_fields, "adVarWChar");
	_typedatum.Mixin(config.GetTokens("CONFIG.Numbers", ",") , "adDouble"); 
	_typedatum.Mixin(config.GetTokens("CONFIG.DateTime", ",") , "adDBTime"); 
	_typedatum["Timestamp"]="adDate"; 
	_typedatum["Alarm"]="adVarWChar"; // should be in _fields
	_typedatum["Shift"]="adInteger"; //

	_sCostFcns =  config.getsection("COSTFCNS");
	_events = config.GetTokens("CONFIG.Events", ","); 

	// Archive information
	_archivepath =  config.GetSymbolValue("CONFIG.ARCHIVEPATH", ::ExeDirectory()).c_str();
	_ArchiveFields = config.GetSymbolValue("CONFIG.Archive", ::ExeDirectory()).c_str();

	// Shift information
	std::string shiftchanges =  config.GetSymbolValue("CONFIG.SHIFTCHANGES", L"00:00,08:00,16:00").c_str();
	std::vector<std::string> shifttimes =Tokenize(shiftchanges, ",", true);
	for(int i=0; i< shifttimes.size(); i++)
	{
		_shiftchanges.push_back(GetShiftTime(shifttimes[i]));
		// shift i+1 must be > shift i
	}

	_delay = _delay / 1000;

	if(_delay == 0) 
		_delay=1;

	std::vector<std::string> _faults = config.GetTokens("CONFIG.Fault", ","); 
	_alarmHandler.Configure(_faults,_archivepath,_sMachine);

	_dbConnection = config.GetSymbolValue("CONFIG.DbConnection", "CMSD").c_str();

	//odbc.open("ConsolidatedData","root","bingo");
	odbc.open(_dbConnection,"root","bingo");
	odbc.createSchema("Factory");
	odbc.deleteTable("Factory", sMachine+"Events");
	odbc.createTable("Factory", sMachine+"Events",_dbeventfields, _typedatum);
	
	_alarmColumns = TrimmedTokenize("Severity,RaisedBy,Description,Program,RaisedAt,ResolvedAt,TBF,TTR",",");
	_typedatum.Mixin(_alarmColumns, "adVarWChar");
	_typedatum["ResolvedAt"]=_typedatum["RaisedAt"]="adDate";
	_typedatum["TBF"]=_typedatum["TTR"]="adTime";// 00:00:00
	odbc.deleteTable("Factory", "Alarms");
	odbc.createTable("Factory", "Alarms",TrimmedTokenize(_alarmHandler._faultitems,","),_typedatum);

	_programColumns= TrimmedTokenize("Timestamp,Machine,Shift,program,Duration,Machining,Faulted,RpmTotal",",");
	_typedatum["Faulted"]="adDBTime"; // seconds
	_typedatum["RpmTotal"]="adInteger"; // revolutions
	
	odbc.deleteTable("Factory", "Programs");
	odbc.createTable("Factory", "Programs",_programColumns,_typedatum);

}
void CHtmlTableSnapshots::Exit()
{
	GLogger << FATAL << "CHtmlTableSnapshots::Exit()" << std::endl; 
	_parser.Release();
	::CoUninitialize();
}
void CHtmlTableSnapshots::Init()
{
	GLogger << FATAL << "CHtmlTableSnapshots::Init()" << std::endl; 
	HRESULT hr;
	COleDateTime now;

	hr = ::CoInitialize(NULL);
	_set_se_translator( trans_func );  // correct thread?

	//html = parser.CreateHtmlDocument();
	//_snapshot->SetDocumentText(html);
	StoreShift(_currentshift+1);
	SetTooltip("MTConnect Dashboard\r\n" + _sMachine);
	shifttimer.restart();
}
void CHtmlTableSnapshots::ExcelArchive(int saveshift)
{
	COleDateTime now = COleDateTime::GetCurrentTime();
	// FIXME: Check if any parts were actually made
	std::string filename=_archivepath;
	filename+=this->_sMachine+"Log";
	filename+=(LPCSTR) now.Format("%y_%m_%d");
	filename+=StdStringFormat("Shift%d", saveshift+1);
	filename+=".csv"; 
	_csvarchiver.write(filename.c_str(),_headers, _typedatum, datum);
}
void CHtmlTableSnapshots::DbArchive()
{
	CDBLogger db;
	COleDateTime now = COleDateTime::GetCurrentTime();
	std::string dbfile=_archivepath + _sMachine + "LogCurrent.mdb";
	if( GetFileExists(dbfile) && ((GetFileSize(dbfile.c_str())>> 20) > 20) ) // larger than 20Mb  - archive
	{
		std::string dbfile2 =_archivepath + _sMachine + "Log" + (LPCSTR) now.Format("%y_%m") + ".mdb";
		MoveFile(dbfile.c_str(),dbfile2.c_str()); // should "delete" dbfile

	}
	if(!GetFileExists(dbfile))
	{
		db.CreateLogDB(dbfile, _fields, _typedatum);
	}

	for(int i=0; i< datum.size(); i++)
	{
		DataDictionary data=datum[i];
		std::vector<std::string> values;
		for(int i=0; i< _fields.size(); i++)
		{
			std::string value = data[_fields[i]];
			if(value=="UNAVAILABLE")
				value = "";
			if(value.find("--")!= std::string::npos)
				value = "";
			//if(_dateTimefields.find(_fields[i]) != std::string::npos)
			//{
			//	value =  DataDictionary::HrMinSecFormat(ConvertString<double>(value,0.0)); 
			//}

			values.push_back(value);

		}
		db.AddRow(dbfile,_fields,_typedatum, values);
	}
}
bool CHtmlTableSnapshots::CheckFault()
{
	int n = _alarmHandler.GetNumberAlarms();
	datum[0]["Alarm"] = _alarmHandler.CheckFault(datum[0]);

	// Check for detection of new alarm 
	if(n != _alarmHandler.GetNumberAlarms())
		return true; // new alarm found
	return false;
}
bool CHtmlTableSnapshots::IsMachining(DataDictionary cycledatum)
{
	return (ConvertString<int>(cycledatum["Srpm"], 0) >0);
}
bool CHtmlTableSnapshots::IsFaulted(DataDictionary cycledatum)
{
	return !cycledatum["Alarm"].empty();
}
bool CHtmlTableSnapshots::Triggered(std::vector<std::string> events,DataDictionary& cycledatum, DataDictionary& lastcycledatum)
{
	for(int i=0; i< events.size(); i++)
	{
		if( lastcycledatum[events[i]] != cycledatum[events[i]])
			return true;
	}
	return false;
}
int CHtmlTableSnapshots::GetCurrentShift()
{
	COleDateTime now = COleDateTime::GetCurrentTime();
	int minute = now.GetHour() * 60 + now.GetMinute();
	if(minute < _shiftchanges[0])
		return _shiftchanges.size();
	for(int i=1; i<= _shiftchanges.size(); i++)
	{
		int high = (i<_shiftchanges.size())? (_shiftchanges[i]-1) : _shiftchanges[i-1]+ _shiftchanges[0];
		if(minute >= _shiftchanges[i-1]  && minute <= high )
		{
			return i;
		}
	}
	return 1;
}

bool CHtmlTableSnapshots::IsEndOfProgram(DataDictionary cycledatum,DataDictionary lastcycledatum, std::vector<std::string> 	events)
{
	// Detect change programming event - program,power,PartCountAct, line<lastline
	if(cycledatum.size() > 0)
	{
		for(int i=0; i< events.size(); i++)
		{
			if( lastcycledatum[events[i]] != cycledatum[events[i]])
				return true;
		}
		if(ConvertString<long>(cycledatum["line"],0) <  ConvertString<long>(lastcycledatum["line"],0))
			return true;
	}
	return false;
}

void CHtmlTableSnapshots::Cycle()
{
	GLogger << FATAL << "CHtmlTableSnapshots::Cycle()" << std::endl; 
	double machineduration, totalduration, faultduration;
	std::string html;
	std::vector<DataDictionary>  cycledatum ;
	boost::timer machiningtimer;
	_mRunning=true;

	Init();
	_currentshift=GetCurrentShift();
	while(_mRunning)
	{
		try {
			// Only 1 datum returned, sequences found to inexact
			bEventTriggered=0;
			cycledatum = _parser.ReadStream(_ipaddr);

			// Detect change programming event - program,power,PartCountAct, line<lastline
			if(cycledatum.size() > 0)
			{
				cycledatum[0]["Shift"]= GetCurrentShift();
				bEventTriggered= IsEndOfProgram(cycledatum[0],lastcycledatum, _events);
				// Save program data before data is cleared.
				// Conflict here - either PartCountAct or program name changes, don't count both. Likewise line
				if(datum.size()!=0 && IsEndOfProgram(cycledatum[0],lastcycledatum, TrimmedTokenize("PartCountAct,program",",")))
					odbc.insert("Factory","Programs",_programColumns,datum[0], _typedatum);
			}

			if(cycledatum.size() == 0)
			{
				// MTConnect agent communication error - agent down or computer down
				cycledatum.push_back(DataDictionary());
				cycledatum[0]["power"]= "OFF";
				cycledatum[0]["Shift"]= GetCurrentShift();
				machineduration=faultduration=0;
				if(lastcycledatum["power"]!=cycledatum[0]["power"] )
				{
					totalduration=0;
					datum.insert(datum.begin(),cycledatum.begin(), cycledatum.end());
				}
				else
					totalduration+= machiningtimer.elapsed();

				if(datum.size()==0)
					datum.insert(datum.begin(),cycledatum.begin(), cycledatum.end());
				lastcycledatum=cycledatum[0];
			}
			else if(datum.size()==0 && cycledatum.size() > 0)
			{	
				totalduration=machineduration=faultduration=0;
				// This is the first go round
				datum.insert(datum.end(),cycledatum.begin(), cycledatum.end());
			}
			else if(cycledatum.size() > 0 && bEventTriggered) //  lastcycledatum["program"] != cycledatum[0]["program"])
			{
				totalduration=machineduration=faultduration=0;
				datum.insert(datum.begin(),cycledatum.begin(), cycledatum.end());
			}
			else if(cycledatum.size() > 0)
			{
				totalduration+= machiningtimer.elapsed(); 
				if(IsMachining(cycledatum[0])) //  ConvertString<int>(cycledatum[0]["Srpm"], 0) >0)
				{
					machineduration+=machiningtimer.elapsed();
					shiftbusytime+=machiningtimer.elapsed();
				}
				datum[0]=cycledatum[0]; // copy new data in case e.g., rpm changes.

				// No change in datum length - just update numbers
				datum[0].Update(machiningtimer.elapsed());
			}
			lastcycledatum=cycledatum[0];

			
			// Update non MTConnect information
			datum[0]["Timestamp"]= GetTimeStamp(LOCAL);
			datum[0]["Machine"]= _sMachine;
			//datum[0]["Duration"] = DataDictionary::HrMinSecFormat(totalduration); 
			//datum[0]["Machining"]= DataDictionary::HrMinSecFormat(machineduration); 
			datum[0]["Duration"] = ToString(totalduration); 
			datum[0]["Machining"]= ToString(machineduration); 
			datum[0]["Elapsed"]= ToString(machiningtimer.elapsed()); 
			datum[0]["NewEvent"]= ToString(bEventTriggered); 
			datum[0]["OEE"] = ToString(shiftbusytime/shifttimer.elapsed() * 100.0 ) ;
			datum[0]["Shift"]= ToString(_currentshift); 

			// Check for detection of new alarm - will trigger some recalculations
			std::string sMTBF, sMTTR;
			if(CheckFault())
			{
				_alarmHandler.CalculateMeanTimes(sMTBF, sMTTR);
				datum[0]["MTBF"]= sMTBF;
				datum[0]["MTTR"]= sMTTR;
			}
			else
			{
				datum[0]["MTBF"]= lastdatum["MTBF"];
				datum[0]["MTTR"]= lastdatum["MTTR"];
			}

			if(IsFaulted(datum[0]))
			{
				faultduration+=machiningtimer.elapsed();
				datum[0]["Faulted"]= ToString(faultduration); 
			}

			static char * Events [] ={ "program","power","PartCountAct","mode","execution", "Alarm"};
			static std::vector<std::string> events(Events, Events + sizeof Events / sizeof Events[ 0 ]);
			bool bTriggered = Triggered(events,datum[0], lastdatum);
			if(bTriggered)
			{
				odbc.insert("Factory",_sMachine+"Events",_dbeventfields,datum[0],_typedatum);
			}

			if(stricmp(datum[0]["power"].c_str(),"OFF")==0) _currentstate= "OFF";
			else if(stricmp(datum[0]["mode"].c_str(),"AUTO")!=0) _currentstate= "MANUAL";
			else if(!datum[0]["Alarm"].empty()) _currentstate= "FAULTED";
			else if(IsMachining(datum[0]))  _currentstate= "BUSY"; 
			else if(stricmp(datum[0]["execution"].c_str(),"IDLE")==0) _currentstate= "IDLE";
			else if(stricmp(datum[0]["execution"].c_str(),"RUNNING")!=0) _currentstate= "PAUSED";

			_statetiming[_currentstate]+= machiningtimer.elapsed();

			UpdateCostFcns();
			StoreSnapshot(CreateHtmlTable(datum));

			if(datum[0]["controllermode"]=="MANUAL")
				SetState(CHtmlTableSnapshots::MANUAL);
			else if(datum[0]["execution"]=="EXECUTING" || datum[0]["execution"]=="RUNNING")
				SetState(CHtmlTableSnapshots::AUTO_RUNNING);
			else if(datum[0]["execution"]=="IDLE")
				SetState(CHtmlTableSnapshots::AUTO_IDLE);
			else if(datum[0]["execution"]=="STOPPED")
				SetState(CHtmlTableSnapshots::STOPPED);
			//else if(datum[0]["execution"]=="STOPPED")
			//	SetState(CHtmlTableSnapshots::FAULT);


			// Update GUI
			Update();
			lastdatum=datum[0];

			int saveshift=_currentshift;
			_currentshift=GetCurrentShift();
			if(saveshift!=_currentshift)
			{
				StoreShift(_currentshift);
				ExcelArchive(saveshift);
				//DbArchive();			
				Clear(); // clear datum
			}

			// Check if shift change, if so, save data to excel
			// Might be better to use waiting timer.
			//{
			//	now = COleDateTime::GetCurrentTime();
			//	minute = now.GetHour() * 60 + now.GetMinute();

			//	for(int i=0; i< _shiftchanges.size(); i++)
			//	{
			//		//if(minute == _shiftchanges[i] &&  _currentshift!=i)
			//		if(minute >= (_shiftchanges[i]-1) && minute <= (_shiftchanges[i]+1) &&  _currentshift!=i)
			//		{
			//			_currentshift=i;
			//			int saveshift =  ((i-1)< 0 ? _shiftchanges.size() - 1 : i-1 );
			//			StoreShift(_currentshift+1);

			//			ExcelArchive(saveshift);
			//			DbArchive();

			//			// clear datum
			//			Clear();
			//			break;
			//		}
			//	}
			//}
#if 0
			if(datum.size() > 2)
			{
				DbArchive();
			}
#endif
			machiningtimer.restart();
			// Sleep a second
			boost::xtime xt;
			boost::xtime_get(&xt, boost::TIME_UTC);
			xt.sec += _delay; 
			this->m_thread.sleep(xt);
		}
		catch(std::exception e)
		{
			AtlTrace("%s%s", "CEchoService::serviceThread() exception " , e.what());
		}
		catch(...)
		{
			AtlTrace("CEchoService::serviceThread() exception ");
		}
	}
	Exit();
}
std::string  CHtmlTableSnapshots::CreateHtmlTable(DataDictionary data)
{
	std::string updatetable;
	std::string style;
	
	updatetable += "<TABLE class=\"gridtable\">\n";
	updatetable +=   "<TR>";
	std::string skip( "estop,controllermode,PartCountActual,avail,PartCountBad,power,probed,ProbeNumber,probe,path_feedratefrt" );
	for(DataDictionary::iterator it = data.begin(); it!=data.end(); it++)
	{
		if(skip.find((*it).first) != std::string::npos)
			continue;
		updatetable +=   "<TH> " + (*it).first    + "</TH> ";
	}
	updatetable +=   "</TR>\n";
	updatetable +=   "<TR>\n";
	for(DataDictionary::iterator it = data.begin(); it!=data.end(); it++)
	{
		style.clear();
		if(skip.find((*it).first) != std::string::npos)
			continue;
		if((*it).first == "Outtol")
		{
			
		}
		if((*it).first == "execution")
		{	
			if((*it).second == "READY")  
				style =   "style=\"background-color:lightblue;\"";
			if((*it).second == "ACTIVE")  
				style =    "style=\"background-color:lightgreen;\"";
		}

		updatetable +=   "<TD " + style + "> "+ (*it).second + "</TD>" ;
	}
	updatetable +=   "</TR>\n";

	updatetable += "</TABLE>\n";
	return updatetable;
}
std::string  CHtmlTableSnapshots::CreateHtmlTable(std::vector<DataDictionary> datum)
{
	std::string htmltable;

	if(datum.size() < 1)
		return "";

	htmltable += "<TABLE class=\"gridtable\">\n";
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
std::string  CHtmlTableSnapshots::CreateHtmlRow(DataDictionary data)
{
	std::string htmltable;
	std::string style;

	for(int i=0; i< _fields.size(); i++)
	{
		double dVal=0.0;
		style.clear();
		std::string value = data[_fields[i]]; //(*it).second;
		std::string field = _fields[i]; //  (*it).first

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
			if(value == "IDLE" || value == "PAUSED")  
			{
				style =   "style=\"background-color:lightblue;\"";
			}
			if(value == "EXECUTING" || value == "RUNNING")  
			{
				style =    "style=\"background-color:green;\"";
			}
			if(value == "STOPPED")  
				style =    "style=\"background-color:red;\"";
		}

		if(value == "UNAVAILABLE")
			value="<CENTER>--</CENTER>";
		if(_dateTimefields.find(field) != std::string::npos)
		{
			value =  DataDictionary::HrMinSecFormat(ConvertString<double>(value,0.0)); 
			style += " align=\"right\"";
		}
		if(_numberfields.find(field) != std::string::npos && sscanf(value.c_str(),"%lf",&dVal))
		{
			value = StdStringFormat("%9.6f", dVal);
			style += " align=\"right\"";
		}
		if(_formats.find(field)!=_formats.end())
		{
			if(sscanf(value.c_str(),"%lf",&dVal))
			value = StdStringFormat(_formats[field].c_str(), dVal);
		}
		htmltable +=   "<TD " + style + "> "+ value + "</TD>\n" ;
	}

	return htmltable;
}

extern void Interpret(DataDictionary &vars, std::vector<std::string> script);

void CHtmlTableSnapshots::UpdateCostFcns()
{
	// Note there will no usable data if the mtconnect agent is down ... 
	if(datum.size() ==0)
		return;

	if(_sCostFcns.size() ==0)
		return;
	
	_kpidatum.insert(datum[0].begin(), datum[0].end());
	Interpret(_kpidatum, _sCostFcns);
	datum[0].insert(_kpidatum.begin(), _kpidatum.end());
	int n=0;
}
