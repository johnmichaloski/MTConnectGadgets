//
// windows7.h
//


#ifndef windows_7
#define windows_7


/**
<requestedExecutionLevel
level="asInvoker|highestAvailable|requireAdministrator"
uiAccess="true|false"/>


*/


inline BOOL ElevateSecurityAttribute(SECURITY_ATTRIBUTES * pSA)
{

static TCHAR secDescriptor[SECURITY_DESCRIPTOR_MIN_LENGTH];

PSECURITY_DESCRIPTOR pSecDesc;

PACL pAcl = NULL;

BOOL fAclPresent = FALSE;

BOOL fAclDefaulted = FALSE;

BOOL bRetval = FALSE;

pSA->nLength = sizeof(SECURITY_ATTRIBUTES);

pSA->bInheritHandle = FALSE;

pSA->lpSecurityDescriptor = &secDescriptor;

InitializeSecurityDescriptor(pSA->lpSecurityDescriptor, SECURITY_DESCRIPTOR_REVISION);

SetSecurityDescriptorDacl(pSA->lpSecurityDescriptor, TRUE, 0, FALSE);

bRetval = ConvertStringSecurityDescriptorToSecurityDescriptor(L"S:(ML;;NW;;;LW)", // "low integrity"
         SDDL_REVISION_1, &pSecDesc, NULL);

bRetval = GetSecurityDescriptorSacl(pSecDesc, &fAclPresent, &pAcl, &fAclDefaulted);

return SetSecurityDescriptorSacl(pSA->lpSecurityDescriptor, TRUE, pAcl, FALSE);

}



inline void SetFilePermission(LPCTSTR FileName) 
{ 
  PSID pEveryoneSID = NULL; 
  BOOL a= TRUE;
         BOOL b= TRUE;
         BOOL c= TRUE;
         DWORD d= 0;
         DWORD ret = 0;
         PACL pACL = NULL; 
  EXPLICIT_ACCESS ea[1]; 
  SID_IDENTIFIER_AUTHORITY SIDAuthWorld = SECURITY_WORLD_SID_AUTHORITY; 
 
  // Create a well-known SID for the Everyone group. 
  a = AllocateAndInitializeSid(&SIDAuthWorld, 1, 
                 SECURITY_WORLD_RID, 
                 0, 0, 0, 0, 0, 0, 0, 
                 &pEveryoneSID); 
         if(!a)
                 DbgOut("SID initialization failed");
  // Initialize an EXPLICIT_ACCESS structure for an ACE. 
  // The ACE will allow Everyone read access to the key. 
  ZeroMemory(&ea, 1 * sizeof(EXPLICIT_ACCESS)); 
  ea[0].grfAccessPermissions = 0xFFFFFFFF; 
  ea[0].grfAccessMode = GRANT_ACCESS; 
  ea[0].grfInheritance= NO_INHERITANCE; 
  ea[0].Trustee.TrusteeForm = TRUSTEE_IS_SID; 
  ea[0].Trustee.TrusteeType = TRUSTEE_IS_WELL_KNOWN_GROUP; 
  ea[0].Trustee.ptstrName = (LPTSTR) pEveryoneSID; 
 
  // Create a new ACL that contains the new ACEs. 
  ret = SetEntriesInAcl(1, ea, NULL, &pACL); 

                 if(ret != ERROR_SUCCESS)
                 DbgOut("ACL entry failed");
         
  // Initialize a security descriptor.  
  PSECURITY_DESCRIPTOR pSD = (PSECURITY_DESCRIPTOR) LocalAlloc(LPTR, 
                            SECURITY_DESCRIPTOR_MIN_LENGTH); 
 
  b = InitializeSecurityDescriptor(pSD,SECURITY_DESCRIPTOR_REVISION); 
         if(!b)
                 DbgOut("Security Descriptor initialization failed");
  
  // Add the ACL to the security descriptor. 
  c = SetSecurityDescriptorDacl(pSD, 
        TRUE,   // bDaclPresent flag  
        pACL, 
        FALSE);  // not a default DACL 
         if(!c)
                  DbgOut("SetSecurityDescriptorDacl failed");
  
  //Change the security attributes 
 //  d = SetFileSecurity(FileName, DACL_SECURITY_INFORMATION, pSD); 
         SetNamedSecurityInfo(L"C:\\Program Files\\Mydir\\My.log",SE_FILE_OBJECT,DACL_SECURITY_INFORMATION,pSD,NULL,NULL,NULL);    
         if(d != ERROR_SUCCESS)
                 DbgOut("SetFileSecurity failed");
  if (pEveryoneSID) 
    FreeSid(pEveryoneSID); 
  if (pACL) 
    LocalFree(pACL); 
  if (pSD) 
    LocalFree(pSD); 
}


#endif