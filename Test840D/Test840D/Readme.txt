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
