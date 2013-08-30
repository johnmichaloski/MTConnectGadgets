// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

#include "aboutdlg.h"
#include "MainDlg.h"

#include "atlstr.h"
#include "Misc.h"
#include <algorithm>
#include "ATLComTime.h"
#include "MinPing.h"

// http://www.microsoft.com/msj/1199/comsecurity/comsecurity.aspx
// may want to consider boost enum/string mapper.

//The client and the server can each call CoInitializeSecurity to specify their respective security blankets. 

//When the application is acting as a server, these parameters are relevant: 
//	- an ACL, 
//	- a list of authentication service/authorization service/principal name tuples, 
//	- an authentication level. 

//A server's call to CoInitializeSecurity, whether implicit or explicit, determines the server's security blanket, which remains fixed.

//When the application is acting as a client, the following values passed to CoInitializeSecurity are relevant: 
//	-	an authentication level, 
//	-	an impersonation level, 
//	-	the authentication identity, 
//	-	and capabilities. 

// A client's implicit or explicit call to CoInitializeSecurity indicates the security blanket that the client wants.




/*


None (RPC_C_AUTHN_LEVEL_NONE)
No authentication is performed during the communication between client and server. All security settings are ignored. This authentication level can be set only if the authentication service level is RPC_C_AUTHN_NONE.

Default (RPC_C_AUTHN_LEVEL_DEFAULT)
COM chooses the authentication level by using its normal security blanket negotiation. It will never choose an authentication level of None.

Connect (RPC_C_AUTHN_LEVEL_CONNECT)
The normal authentication handshake occurs between the client and server, and a session key is established but that key is never used for communication between the client and server. All communication after the handshake is insecure.


The client can set an impersonation level that determines to what extent the server will be able to act as the client. 
If the client grants enough authority to the server, the server can impersonate (pretend to be) the client. 
When impersonating the client, the server is given access to only those objects or resources that the client has permission to use. 
The server, acting as a client, can also enable cloaking to mask its own identity and project the client's identity in calls to other COM components. 

Impersonation Levels

anonymous (RPC_C_IMP_LEVEL_ANONYMOUS)
The client is anonymous to the server. The server process can impersonate the client, but the impersonation token does not contain any information about the client. This level is only supported over the local interprocess communication transport. All other transports silently promote this level to identify.

identify (RPC_C_IMP_LEVEL_IDENTIFY)
The system default level. The server can obtain the client's identity, and the server can impersonate the client to do ACL checks. 

impersonate (RPC_C_IMP_LEVEL_IMPERSONATE)
The server can impersonate the client's security context while acting on behalf of the client. The server can access local resources as the client. If the server is local, it can access network resources as the client. If the server is remote, it can access only resources that are on the same computer as the server.

delegate (RPC_C_IMP_LEVEL_DELEGATE) ONLY IN SAME DOMAIN

Cloaking : http://msdn.microsoft.com/en-us/library/ms683778(VS.85).aspx 


*/

//#import "AtlLockScreen.tlb"
//using namespace AtlLockScreenLib;


BOOL CMainDlg::PreTranslateMessage(MSG* pMsg)
{
	return CWindow::IsDialogMessage(pMsg);
}

BOOL CMainDlg::OnIdle()
{
	return FALSE;
}

//#define HKEY_CLASSES_ROOT                   (( HKEY ) (ULONG_PTR)((LONG)0x80000000) )
//#define HKEY_CURRENT_USER                   (( HKEY ) (ULONG_PTR)((LONG)0x80000001) )
//#define HKEY_LOCAL_MACHINE                  (( HKEY ) (ULONG_PTR)((LONG)0x80000002) )
//#define HKEY_USERS                          (( HKEY ) (ULONG_PTR)((LONG)0x80000003) )
//#define HKEY_PERFORMANCE_DATA               (( HKEY ) (ULONG_PTR)((LONG)0x80000004) )
//#define HKEY_PERFORMANCE_TEXT               (( HKEY ) (ULONG_PTR)((LONG)0x80000050) )
//#define HKEY_PERFORMANCE_NLSTEXT            (( HKEY ) (ULONG_PTR)((LONG)0x80000060) )

template<typename T>
static STDMETHODIMP SetRegistryKeyValue(HKEY hive, std::wstring fullykey, std::wstring value)
{
	HRESULT hr = S_OK;
	CRegKey regkey;
	std::wstring key =  fullykey.substr( 0, fullykey.find_last_of( '\\' ) );
	std::wstring keyonly =   fullykey.substr( fullykey.find_last_of( '\\' ) +1 );

	if(ERROR_SUCCESS != regkey.Create(hive, key.c_str()))
	{

		regkey.Open(hive, key.c_str(),KEY_READ | KEY_WRITE);
	}


	if( stricmp( typeid(T).name() , "std::wstring")==0)
	{
		hr =regkey.SetValue( value.c_str(),keyonly.c_str() );

	}
	else if( stricmp(typeid(T).name() , "unsigned long")==0)
	{
		DWORD d =ConvertString<DWORD>((LPCTSTR) value.c_str(),0);

		hr =regkey.SetDWORDValue(keyonly.c_str(), d);

	}


	if(ERROR_SUCCESS != hr)
	{
		OutputDebugString(_T("Registry value failed"));
		hr= E_FAIL;
	}

	regkey.Flush();
	regkey.Close();

	return hr;
}

std::map<std::wstring, std::wstring> CMainDlg::ParseIni(std::wstring inisection)
{
	CStringVector tmp;
	std::map<std::wstring, std::wstring> pairs;
	std::wstring buffer(2048, '0');;

	int len = GetPrivateProfileSection(inisection.c_str(),&buffer[0], buffer.size(), inifile);
	for(int i=0; i< len; i++) 
	{
		if(buffer[i]==0) 
			buffer[i]=L'\n';
	}
	CStringVector lines = Tokenize((LPCWSTR) std::wstring( buffer.begin(), buffer.begin() + len ).c_str(), "\n" );
	for(int i=0; i< lines.size(); i++)
	{
		int n;
		lines[i]=lines[i].Trim();
		if((n=lines[i].Find('='))<0)
			continue;
		pairs[(LPCTSTR) lines[i].Mid(0,n) ] =(LPCTSTR) lines[i].Mid(n+1);
	}
	return pairs;
}

LRESULT  CMainDlg::OnBnClickedRegistrybutton(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	
	std::map<std::wstring, std::wstring> keys = ParseIni(L"KEYS");

	for( std::map<std::wstring, std::wstring>::iterator it = keys.begin(); it!=keys.end(); it++)
	{
		if((*it).first.substr(0,4) == L"HKLM")
		{
			SetRegistryKeyValue<DWORD>(HKEY_LOCAL_MACHINE, (*it).first.substr(5).c_str(),(LPCTSTR)(*it).second.c_str());
		}
		else if((*it).first.substr(0,4) == L"HKCU")
		{

		}

	}
	return 0;


}

LRESULT CMainDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	USES_CONVERSION;
	int i;
	inifile = GetExeDirectory().c_str(); 
	inifile += L"config.ini";

	// center the dialog on the screen
	CenterWindow();

	// set icons
	HICON hIcon = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME), 
		IMAGE_ICON, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON), LR_DEFAULTCOLOR);
	SetIcon(hIcon, TRUE);
	HICON hIconSmall = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME), 
		IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
	SetIcon(hIconSmall, FALSE);

	// register object for message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->AddMessageFilter(this);
	pLoop->AddIdleHandler(this);

	UIAddChildWindowContainer(m_hWnd);
	_cStatus = GetDlgItem(IDC_TESTSTATUS);
	_authSecurityCombo =  GetDlgItem(IDC_AUTHNCOMBO);
	_impersonationSecurityCombo =  GetDlgItem(IDC_IMPERSCOMBO3);

	_authnCombo =  GetDlgItem(IDC_AUTHNCOMBO2);
	_authzCombo =  GetDlgItem(IDC_AUTHZCOMBO3);
	_authnlevelCombo =  GetDlgItem(IDC_AUTHENLEVELCOMBO4);
	_impersonationlevelCombo =  GetDlgItem(IDC_IMPERSLEVELCOMBO5);
	_usersCombo=  GetDlgItem(IDC_USERSCOMBO3);
	_ipaddrControl=GetDlgItem(IDC_IPADDRESS);
	

	// CoInitializeSecurity
	for(i=0;  i < _enums._authenums.size(); i++)
		_authSecurityCombo.AddString(_enums._authenums[i]);

	for(i=0;  i < _enums.implevelitems.size(); i++)
		_impersonationSecurityCombo.AddString(_enums.implevelitems[i]);

	// CoCreateInstance
	for(i=0;  i < _enums.authnitems.size(); i++)
		_authnCombo.AddString(_enums.authnitems[i]);
	
	for(i=0;  i < _enums.authzitems.size(); i++)
		_authzCombo.AddString(_enums.authzitems[i]);
	
	for(i=0;  i < _enums.authenlevelitems.size(); i++)
		_authnlevelCombo.AddString(_enums.authenlevelitems[i]);

	for(i=0;  i < _enums.implevelitems.size(); i++)
		_impersonationlevelCombo.AddString(_enums.implevelitems[i]);

	n_authLevelComSecurityEnum=RPC_C_AUTHN_LEVEL_CONNECT;
	n_impLevelComSecurityEnum=RPC_C_IMP_LEVEL_IDENTIFY;

	n_authnEnum=RPC_C_AUTHN_WINNT;
	n_authzEnum=RPC_C_AUTHZ_NONE;
	n_authnlevelEnum = RPC_C_AUTHN_LEVEL_NONE;
	n_impersonationlevelEnum=RPC_C_IMP_LEVEL_IDENTIFY;


	std::wstring buffer(2048, '0');;
	int len = GetPrivateProfileSection( L"USERS",&buffer[0], buffer.size(), inifile);
	for(i=0; i< len; i++) 
	{
		if(buffer[i]==0) 
			buffer[i]=L'\n';
	}
	CStringVector lines = Tokenize((LPCWSTR) std::wstring( buffer.begin(), buffer.begin() + len ).c_str(), "\n" );
	for(i=0; i< lines.size(); i++)
	{
		int n;
		lines[i]=lines[i].Trim();
		if((n=lines[i].Find('='))<0)
			continue;
		_users.push_back(lines[i].Mid(n+1));
	}
	if(lines.size()==0)
		_users.push_back("None");

	for(i=0; i< _users.size(); i++)
		_usersCombo.AddString(_users[i]);

	len = ::GetPrivateProfileString(_T("CONFIG"), _T("clsid"), _T(""), &buffer[0], buffer.size(), inifile);
	sClsid= std::wstring( buffer.begin(), buffer.begin() + len ).c_str();

	len = ::GetPrivateProfileString(_T("CONFIG"), _T("ipaddr"), _T("192.168.4.11"), &buffer[0], buffer.size(), inifile);
	server = std::wstring( buffer.begin(), buffer.begin() + len ).c_str();

	_nUser=0;
	Load();



	return TRUE;
}




HRESULT CMainDlg::Connect(void)
{
	HRESULT hr;
	status = COleDateTime::GetCurrentTime().Format();
	std::wstring buffer(1024, '0');;

	try {

	CoInitialize(NULL);

	ComInitializeSecuity dcom;
	dcom.dwAuthnLevel=RPC_C_AUTHN_LEVEL_CONNECT;;
	dcom.dwImpLevel=RPC_C_IMP_LEVEL_IDENTIFY;
	hr=dcom.InitializeSecurity();


	CLSID gOpcServerClsid;
	// OPC.SINUMERIK.MachineSwitch
	sClsid=L"{75d00afe-dda5-11d1-b944-9e614d000000}";  // Siemens 840D OPC Server CLSID : 75d00afe-dda5-11d1-b944-9e614d000000
	if(FAILED(CLSIDFromString(sClsid , &gOpcServerClsid)))
	{
		throw bstr_t(L"CLSIDFromString(_bstr_t(sClsid) , &gOpcServerClsid))) FAILED\n");
		return 0;
	}

	//	Auth_Identity idn((LPCWSTR) domain),(LPCWSTR) user,(LPCWSTR) password);
	//	pAuthIdentityData=idn.GetNullAuth_Identity();
	//	sUserSettings.Format(L"Domain=%s\r\nUser=%s\r\nPassword=%s", 
	//		(LPCWSTR) domain, (LPCWSTR) user,(LPCWSTR) password);

	COAUTHIDENTITY* pAuthIdentityData=NULL; 

	//pAuthIdentityData.dwAuthzSvc  = RPC_C_AUTHZ_NAME; 
	//pAuthIdentityData.dwAuthnLevel  = RPC_C_AUTHN_LEVEL_NONE ; 


	COAUTHINFO athn;
	athn.dwAuthnSvc = RPC_C_AUTHN_WINNT; 
	athn.dwAuthzSvc = RPC_C_AUTHZ_NONE; 
	athn.pwszServerPrincName = NULL;
	athn.dwAuthnLevel =  RPC_C_AUTHN_LEVEL_NONE; 
	athn.dwImpersonationLevel = RPC_C_IMP_LEVEL_IDENTIFY; // n_impersonationlevelEnum;
	athn.dwCapabilities = EOAC_NONE;
	athn.pAuthIdentityData=pAuthIdentityData;

	//COSERVERINFO is the class that stores the name of the server
	COSERVERINFO srvinfo; // = {0, server, NULL, 0}; // Create the object and query for two interfaces
	srvinfo.dwReserved1=0;
	srvinfo.dwReserved2=0;
	srvinfo.pwszName=L"129.6.78.90";
	srvinfo.pAuthInfo=&athn;

	//CoInitializeEx(NULL, COINIT_MULTITHREADED  );
	MULTI_QI mqi[]=
	{ 
		{&IID_IOPCServer, NULL , 0} 
	};

	//hr=CoCreateInstanceEx(
	//	_gOpcServerClsid, // Request an instance of class CLSID_MyBackupService
	//	NULL, // No aggregation
	//	CLSCTX_SERVER, // CLSCTX_SERVER, // Any server is fine
	//	&srvinfo, // Contains remote server name
	//	sizeof(mqi)/sizeof(mqi[0]), // number of interfaces we are requesting (2)
	//	(MULTI_QI        *) &mqi); // structure indicating IIDs and interface pointers

	

	

	//
 //
	//COAUTHIDENTITY* pAuthIdentityData; 
	//CStringVector info = Tokenize(_users[_nUser], ",");
	//if(info.size()<3)
	//{
	//	pAuthIdentityData=NULL;
	//	sUserSettings="No User/Password";
	//}
	//else
	//{

	//}
	//Load();

	//COAUTHINFO athn;
	//athn.dwAuthnSvc = n_authnEnum;
	//athn.dwAuthzSvc = n_authzEnum;
	//athn.pwszServerPrincName = NULL;
	//athn.dwAuthnLevel = n_authnlevelEnum;
	//athn.dwImpersonationLevel = n_impersonationlevelEnum;
	//athn.dwCapabilities = EOAC_NONE;
	//athn.pAuthIdentityData=pAuthIdentityData;
	////athn.pAuthIdentityData = (COAUTHIDENTITY*)idn;

	////COSERVERINFO is the class that stores the name of the server
	//COSERVERINFO srvinfo; // = {0, server, NULL, 0}; // Create the object and query for two interfaces
	//srvinfo.dwReserved1=0;
	//srvinfo.dwReserved2=0;
	//srvinfo.pwszName=server;
	//srvinfo.pAuthInfo=&athn;


	if(FAILED(hr=CoCreateInstanceEx(
		gOpcServerClsid, // Request an instance of class 
		NULL, // No aggregation
		CLSCTX_SERVER, // CLSCTX_SERVER, // Any server is fine
		&srvinfo, // Contains remote server name
		sizeof(mqi)/sizeof(mqi[0]), // number of interfaces we are requesting (2)
		(MULTI_QI        *) &mqi))) // structure indicating IIDs and interface pointers


		throw bstrFormat(L":Test840D CoCreateInstanceEx  FAILED 0x%x = %s\n",  hr, ErrorFormatMessage(hr));

	_pIOPCServer = (IOPCServer *) (mqi[0].pItf); // Retrieve first interface pointer hr=pBackupAdmin->StartBackup(); // use it…

	OPCSERVERSTATUS * pServerStatus=NULL;
	if(FAILED(hr=_pIOPCServer->GetStatus(&pServerStatus)))
	{
		OutputDebugString(bstrFormat(L"COPCBackEnd::Connect Machine  -  GetStatus error 0x%x\n",hr ));
		return E_FAIL;
	}
	TestOPCGroup();

	//status+= L":Test840D Connect Succeded";
	_pIOPCServer->Release();
	}
	catch(bstr_t errmsg)
	{
		status += (LPCWSTR) errmsg;
		OutputDebugString(errmsg);

	}
	catch(...)
	{
		OutputDebugString(bstrFormat(L"Lock  FAILED 0x%x = %s\n",  hr, ErrorFormatMessage(hr)));

	}
	status.Replace(L"\n", L" ");
	_cStatus.SetWindowText(status );
	::CoUninitialize();
	return S_OK;
}

HRESULT CMainDlg::TestOPCGroup(void)
{		
	HRESULT hResult;
	// variables for AddGroup method
	LONG	lTimeBias = -5;				// washington DC (-5) to greenwich meantime 
	FLOAT	fDeadband = 10.0;				// no deadband
	DWORD	dwRevisedUpdateRate = 0;	// revised update rate from server
	OPCHANDLE _hServerHandleGroup=NULL;					// server handle of our group
	long _nOPCServerRate=5000;
	try {
		/////////////////////////////////////////////////////////////////////////////
		//Add group to server
		/////////////////////////////////////////////////////////////////////////////

		// add our group to the OPC server
		if(FAILED(hResult = _pIOPCServer->AddGroup(	
			L"Test",		// name of the new group
			TRUE,					// group is active (sends callbacks)
			_nOPCServerRate,		// update rate of 100 ms
			23111980,				// our client handle of this group
			&lTimeBias,				// time bias
			&fDeadband,				// deadband until server sends change notifications
			LOCALE_USER_DEFAULT,	// LCID of the user
			&_hServerHandleGroup,	// server handle of the group
			&dwRevisedUpdateRate,	// revised update rate
			IID_IOPCItemMgt,		// desired interface of the group
			(LPUNKNOWN*)&_pIOPCItemMgt
			)))
		{
			_pIOPCItemMgt=NULL;
			throw std::wstring (_T("FAIL: Connect() couldn't add group to server!\n"));
		}

		if(FAILED(hResult = AddOPCItem(L"TestItem")))
		{
			throw std::wstring (_T("FAIL: Connect() couldn't add item to group!\n"));
		}
	}
	catch(std::wstring errmsg)
	{
		status += (LPCTSTR)  errmsg.c_str();
	}

	return S_OK;
}
inline WCHAR * WSTRClone(_bstr_t oldstr)
{
	WCHAR *newstr;
	//if(oldstr==NULL)
	//	oldstr=_bstr_t("");

	newstr = (WCHAR*)CoTaskMemAlloc(sizeof(WCHAR) * (wcslen(oldstr) + 1));

	if(newstr) wcscpy_s(newstr, wcslen(oldstr) + 1, oldstr.GetBSTR());
	return newstr;
}
HRESULT CMainDlg::AddOPCItem(std::wstring name) 
{
	// variables for AddItem method
	HRESULT hr=S_OK;
	OPCITEMDEF		opcItemDef[1];			// item definition structure
	OPCITEMRESULT*	popcItemResult =NULL;	// array of item result structures
	HRESULT*		phResultArray = NULL;	// array of result
	try 
	{
		// fill item definition structure with data of our item (/bag/state/opmode)
		opcItemDef[0].szAccessPath=L"";					// no access path description
		opcItemDef[0].szItemID=WSTRClone(L"/Channel/MachineAxis/actToolBasePos[1]");			// ItemID of the variable (BTSS name)
		opcItemDef[0].bActive=TRUE;						// set item active to get notifications, if value changes
		opcItemDef[0].hClient=(OPCHANDLE)0x100;		    // client handle of the item
		opcItemDef[0].dwBlobSize=0;						// no blob
		opcItemDef[0].pBlob=NULL;						//  -"-
		opcItemDef[0].vtRequestedDataType=VT_BSTR;		// value of the item should be delivered as BSTR

		// add our item to the group
		hr=_pIOPCItemMgt->AddItems(	
			1,									// add 1 item...
			opcItemDef,							// with this definition
			(OPCITEMRESULT**)&popcItemResult,	// server data of this item
			(HRESULT**)&phResultArray			// was addition successfull?
			); 

		if(FAILED(hr))
		{
			throw std::wstring ((LPCTSTR)  bstrFormat(L"FAIL: AddOPCItem() generic fai  -   error 0x%x\n",hr ));
		}
		else if(hr==S_FALSE)
		{
		}

		if(phResultArray[0]!=S_OK)
		{
			throw std::wstring (_T("FAIL: AddOPCItem() phResultArray fail\n")); 
			hr=E_FAIL;
		}
	}
	catch( std::wstring errmsg)
	{
		status += (LPCTSTR)  errmsg.c_str();
		OutputDebugString(status);

	}

	if(opcItemDef[0].szItemID!=NULL)
		::CoTaskMemFree( opcItemDef[0].szItemID );

	if(popcItemResult!=NULL)
		::CoTaskMemFree( popcItemResult );

	if(phResultArray!=NULL)
		::CoTaskMemFree( phResultArray );
	return hr;
}
LRESULT CMainDlg::OnBnClickedConnect(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	_cStatus.SetWindowText(L"");
	Connect();
	return 0;
}

LRESULT CMainDlg::OnCbnSelchangeAuthnCombo(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	Save();
	return 0;
}

void CMainDlg::Save(void)
{
	USES_CONVERSION;

	// CoInitializeSecurity
	n_authLevelComSecurityEnum=_authSecurityCombo.GetCurSel();
	n_impLevelComSecurityEnum=_impersonationSecurityCombo.GetCurSel();

	// CoCreateInstance
	n_authzEnum=_authzCombo.GetCurSel();
	n_authnlevelEnum=_authnlevelCombo.GetCurSel();
	n_impersonationlevelEnum=_impersonationlevelCombo.GetCurSel();

	// non-sequential enumerations
	n_authnEnum=_enums.Value((LPCWSTR) _enums.authnitems[_authnCombo.GetCurSel()]);

	// user 
	_nUser=_usersCombo.GetCurSel();


	DWORD  ip;
	_ipaddrControl.GetAddress(&ip);
	server = bstrFormat(L"%d.%d.%d.%d", FIRST_IPADDRESS(ip),  SECOND_IPADDRESS(ip), THIRD_IPADDRESS(ip), FOURTH_IPADDRESS(ip));
}

void CMainDlg::Load(void)
{
	USES_CONVERSION;

	// CoInitializeSecurity
	_authSecurityCombo.SetCurSel(n_authLevelComSecurityEnum);
	_impersonationSecurityCombo.SetCurSel(n_impLevelComSecurityEnum);

	// CoCreateInstance
	_authzCombo.SetCurSel(n_authzEnum);
	_authnlevelCombo.SetCurSel(n_authnlevelEnum);
	_impersonationlevelCombo.SetCurSel(n_impersonationlevelEnum);
	_usersCombo.SetCurSel(_nUser);
	GetDlgItem(IDC_CLSIDTEXT).SetWindowText(sClsid);
	GetDlgItem(IDC_USERINFO).SetWindowText(sUserSettings);
	_ipaddrControl.SetAddress(htonl(inet_addr((LPCSTR) server)));

	// non-sequential enumerations
	_authnCombo.SetCurSel( _enums.Get(n_authnEnum, _enums.authnitems));

}
LRESULT CMainDlg::OnCbnEditAuthnCombo(WORD wNotifyCode, WORD wID, HWND /*hWndCtl*/, BOOL& bHandled)
{
	CString str;
	_usersCombo.GetWindowText(str);
	if(find(_users.begin(), _users.end(), str) == _users.end())
	{
		_users.push_back(str);
		_usersCombo.AddString(str);

	}
	return 0;
}

LRESULT CMainDlg::OnBnClickedPingbutton(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	USES_CONVERSION; 
	Save();
	_cStatus.SetWindowText(_T("") );
	CString status = COleDateTime::GetCurrentTime().Format();
	status+= _T(" ") + CMiniPing().Ping((LPCTSTR) server);
	_cStatus.SetWindowText(status );

	return 0;
}
