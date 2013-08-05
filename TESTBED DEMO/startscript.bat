
pushd .
cd .\AgentDeviceStatus\AgentCmd5
start RunAgent.bat 
popd

Rem wait 10 seconds
ping 127.0.0.1 -n 10 > nul



pushd .
cd .\AgentCmd
start CMSDCommandCell.exe
popd

Rem Just echo Agent status, reads devices
pushd .
cd .\AgentCmdEcho\Agent5
start MTCAgentCmdEcho.exe
popd


pushd .
cd .\MtConnectDboard\Agents5
start MtConnectDboardGui.exe /RegServer
start MtConnectDboard.exe
popd


pushd . 
cd .\AgentViews
start MTConnectStatusEcho.vbs
start MTConnectCmdEcho.vbs
popd



rem start .\SSH\startallherbie.vbs


