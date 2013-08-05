


pushd .
cd .\AgentCmdEcho\Agent5
start MTCAgentCmdEcho.exe
popd

Rem wait 10 seconds
rem ping 127.0.0.1 -n 10 > nul


pushd .
cd .\AgentCmd
rem start CMSDCommandCell.exe
popd


pushd . 
cd .\AgentViews
start MTConnectStatusEcho.vbs
start MTConnectCmdEcho.vbs
popd


rem start .\SSH\startallherbie.vbs


