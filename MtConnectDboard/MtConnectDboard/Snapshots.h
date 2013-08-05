//
// Snapshots.h
//
#pragma once
#if defined( DEBUG) && ( _MSC_VER >= 1600)   // 2010
#import  "c:\\Program Files\\NIST\\proj\\MTConnect\\Nist\\MTConnectGadgets\\MtConnectDboard\\MtConnectDboardGui\\Debug10\\MtConnectDboardGui.exe"
#elif  ( _MSC_VER >= 1600 ) 
#import  "c:\\Program Files\\NIST\\proj\\MTConnect\\Nist\\MTConnectGadgets\\MtConnectDboard\\MtConnectDboardGui\\Debug10\\MtConnectDboardGui.exe"
#elif  defined( DEBUG) && (_MSC_VER >= 1500 && _MSC_VER < 1600)
#import  "c:\\Program Files\\NIST\\proj\\MTConnect\\Nist\\MTConnectGadgets\\MtConnectDboard\\MtConnectDboardGui\\Debug9\\MtConnectDboardGui.exe"
#elif (_MSC_VER >= 1500 && _MSC_VER < 1600)
#import  "c:\\Program Files\\NIST\\proj\\MTConnect\\Nist\\MTConnectGadgets\\MtConnectDboard\\MtConnectDboardGui\\Debug9\\MtConnectDboardGui.exe"
#else
#pragma message("_MSC_VER????")
#endif

namespace MTC=MtConnectDboardGuiLib;

#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>
#include <boost/timer.hpp>

#include "DataDictionary.h"
#include "DataArchiver.h"
#include "MTConnectStreamsParser.h"
#include "Config.h"
#include "AlarmHandler.h"
#include "OdbcArchiver.h"

extern void KillProgram(std::string progname);

__declspec(selectany)_ATL_FUNC_INFO OnResetInfo = {  CC_STDCALL, VT_EMPTY, 1, {VT_BSTR}};

class CHtmlTableSnapshots:
	public IDispEventSimpleImpl<1, CHtmlTableSnapshots, &__uuidof(MtConnectDboardGuiLib::_IDboardNotificationEvents)>
{
public:
	CHtmlTableSnapshots();
	void __stdcall OnReset(BSTR items);

BEGIN_SINK_MAP(CHtmlTableSnapshots)
	SINK_ENTRY_INFO(1, __uuidof(MtConnectDboardGuiLib::_IDboardNotificationEvents), 0x1, OnReset, &OnResetInfo)
END_SINK_MAP()

	enum StateDef { AUTO_IDLE, AUTO_RUNNING, MANUAL, FAULT,STOPPED };
	bool							IsMachining(DataDictionary cycledatum);
	bool							IsFaulted(DataDictionary cycledatum);
	bool							IsEndOfProgram(DataDictionary cycledatum,DataDictionary lastcycledatum,std::vector<std::string> events);
	void							Clear();
	void							Configure(crp::Config &config,
		std::string sMachine, // machine name
		std::string ipaddr, // ip address of agent
		std::string configname // section name to lookup configuration info
		); 
	void							Cycle();
	void							DbArchive();
	void							Disconnect();
	void							ExcelArchive(int nShift);
	void							Exit();
	int								GetCurrentShift();
	void							Init();
	void							Logoff();
	void							Logon();
	void							SetState(StateDef state);
	void							SetTooltip(std::string tooltip){ _tooltip= tooltip; }
	void							Shutdown();
	void							Stop(){ _mRunning=false; }
	void							StoreShift(int shift);
	void							StoreSnapshot(std::string snapshot);
	bool							Triggered(std::vector<std::string> events,DataDictionary& cycledatum, DataDictionary& lastcycledatum);
	void							Update();



	CComPtr<MTC::ICMTConnectTrayIcon> pTrayIcon;
	CComPtr<IWebBrowser2>			GetWebBrowser();
	CComPtr<IHTMLDocument2>			GetDocument(CComPtr<IWebBrowser2>);
	CComPtr<IHTMLElement>			GetElement(CComPtr<IWebBrowser2>, const TCHAR *id);
	HRESULT							SetElementId(CComPtr<IWebBrowser2>, std::string id, std::string str);
	HRESULT							SetDocumentText(std::string cstr);

	OdbcArchiver					odbc;
	std::string						_dbConnection;
	int								bEventTriggered;
	std::vector<std::string>		_dbeventfields;  // state driven raw to event data
	std::vector<std::string>		_alarmColumns;   // alarm db recording
	std::vector<std::string>		_programColumns;   // program db recording

	std::vector<std::string>			_sCostFcns;
	std::string							_snapshot, _lastsnapshot;
	std::vector<std::string>			_snapshots ;
	unsigned int						_nSnapshot;
	std::string							_sShift,_sLastShift;
	StateDef							_state;
	bool								_loggedon;
	std::string							_tooltip, _lasttooltip;
	std::vector<DataDictionary>			datum;
	DataDictionary						lastdatum;
	DataDictionary						lastcycledatum;
	DataDictionary						_kpidatum;
	DataDictionary						_typedatum;
	boost::timer						shifttimer;
	double								shiftbusytime;

	int 								_currentshift;
	std::vector<std::string> 			_events;
	std::vector<int> 					_shiftchanges; // in minutes
	std::string 						_sMachine;
	std::string 						_ipaddr;
	std::string							_archivepath;
	std::string							_headers;
	MTConnectStreamsParser				_parser;
	CsvArchiver							_csvarchiver;
	boost::thread						m_thread;
	bool								_mRunning;
	int									_delay; 
	std::string							_ArchiveFields;

		// Configuration
	std::string							_numberfields;
	DataDictionary						_colormapping;
	DataDictionary						_formats;
	std::vector<std::string>			_fields;
	std::string							_dateTimefields;
	std::vector<std::string>			_KPIList;

	CAlarmHandler						_alarmHandler;
	std::map<std::string,double>		_statetiming;
	std::string							_currentstate;

	std::string							CreateHtmlRow(DataDictionary data);
	std::string							CreateHtmlTable(std::vector<DataDictionary> datum);
	std::string							CreateHtmlTable(DataDictionary data);
	void								UpdateCostFcns();
	bool								CheckFault();
};