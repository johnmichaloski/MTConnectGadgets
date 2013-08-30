HKLM\System\CurrentControlSet\Control\Lsa\limitblankpassworduse   to 0


level="requireAdministrator"

	HKEY hKey = NULL;
		DWORD dwDisposition = 0;
		if (RegCreateKeyEx(
			HKEY_LOCAL_MACHINE, 
			key, 
			0, NULL, 0, KEY_ALL_ACCESS, NULL, &hKey, &dwDisposition
			) != ERROR_SUCCESS) 
		{
			::MessageBoxW( NULL, L"Registration Error 1", L"Registration", MB_OK );
			return E_FAIL;
		}
		regkey.Attach(hKey);



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