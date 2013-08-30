@echo off
setlocal
set data=0&goto doit
:err
@echo Syntax: DCOMErr ON^|OFF
endlocal
goto :EOF
:doit
set key="HKLM\SYSTEM\CurrentControlSet\Control\Lsa"
call :quiet>nul 2>&1
endlocal
goto :EOF
:quiet
reg add %key% /V LimitBlankPasswordUse /T REG_DWORD /F /D %data%
reg add %key% /V restrictanonymous/T REG_DWORD /F /D %data%
 
