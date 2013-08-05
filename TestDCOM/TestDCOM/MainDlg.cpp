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

LRESULT CMainDlg::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// unregister message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->RemoveMessageFilter(this);
	pLoop->RemoveIdleHandler(this);

	return 0;
}

LRESULT CMainDlg::OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CAboutDlg dlg;
	dlg.DoModal();
	return 0;
}

LRESULT CMainDlg::OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add validation code 
	CloseDialog(wID);
	return 0;
}

LRESULT CMainDlg::OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CloseDialog(wID);
	return 0;
}

void CMainDlg::CloseDialog(int nVal)
{
	DestroyWindow();
	::PostQuitMessage(nVal);
}

HRESULT CMainDlg::Connect(void)
{
	HRESULT hr;
	CString status = COleDateTime::GetCurrentTime().Format();
	std::wstring buffer(1024, '0');;

	try {

	CoInitialize(NULL);

	ComInitializeSecuity dcom;
	dcom.dwAuthnLevel=n_authLevelComSecurityEnum;
	dcom.dwImpLevel=n_impLevelComSecurityEnum;
	hr=dcom.InitializeSecurity();

	MULTI_QI mqi[]=
	{ 
		{&__uuidof(IUnknown), NULL , 0} 
	};



	CLSID gOpcServerClsid;
	// OPC.SINUMERIK.MachineSwitch
	// sClsid=L"{1BD3938A-878F-4737-8DEC-3E3E3D4F6F4F}";
	if(FAILED(CLSIDFromString(sClsid , &gOpcServerClsid)))
	{
		throw bstr_t(L"CLSIDFromString(_bstr_t(sClsid) , &gOpcServerClsid))) FAILED\n");
		return 0;
	}
 
	COAUTHIDENTITY* pAuthIdentityData; 
	CStringVector info = Tokenize(_users[_nUser], ",");
	if(info.size()<3)
	{
		pAuthIdentityData=NULL;
		sUserSettings="No User/Password";
	}
	else
	{
		Auth_Identity idn((LPCWSTR) info[0].Trim(),(LPCWSTR) info[1].Trim(),(LPCWSTR) info[2].Trim());
		pAuthIdentityData=idn.GetNullAuth_Identity();
		sUserSettings.Format(L"Domain=%s\r\nUser=%s\r\nPassword=%s", 
			(LPCWSTR) info[0].Trim(), (LPCWSTR) info[1].Trim(),(LPCWSTR) info[2].Trim());

	}
	Load();

	COAUTHINFO athn;
	athn.dwAuthnSvc = n_authnEnum;
	athn.dwAuthzSvc = n_authzEnum;
	athn.pwszServerPrincName = NULL;
	athn.dwAuthnLevel = n_authnlevelEnum;
	athn.dwImpersonationLevel = n_impersonationlevelEnum;
	athn.dwCapabilities = EOAC_NONE;
	athn.pAuthIdentityData=pAuthIdentityData;
	//athn.pAuthIdentityData = (COAUTHIDENTITY*)idn;

	//COSERVERINFO is the class that stores the name of the server
	COSERVERINFO srvinfo; // = {0, server, NULL, 0}; // Create the object and query for two interfaces
	srvinfo.dwReserved1=0;
	srvinfo.dwReserved2=0;
	srvinfo.pwszName=server;
	srvinfo.pAuthInfo=&athn;


	if(FAILED(hr=CoCreateInstanceEx(
		gOpcServerClsid, // Request an instance of class CLSID_MyBackupService
		NULL, // No aggregation
		CLSCTX_ALL, // CLSCTX_SERVER, // Any server is fine
		&srvinfo, // Contains remote server name
		sizeof(mqi)/sizeof(mqi[0]), // number of interfaces we are requesting (2)
		(MULTI_QI        *) &mqi))) // structure indicating IIDs and interface pointers


		throw bstrFormat(L":TestDCOM CoCreateInstanceEx  FAILED 0x%x = %s\n",  hr, ErrorFormatMessage(hr));


	IUnknown * m_pExe = (IUnknown *) (mqi[0].pItf); 
	status+= L":TestDCOM Connect Succeded";
	//	hr=m_pExe->Lock();
	hr=m_pExe->Release();
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
