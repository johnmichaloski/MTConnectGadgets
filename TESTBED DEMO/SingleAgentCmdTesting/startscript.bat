
pushd .
cd .\AgentDeviceStatus1
start RunAgent.bat 
popd

Rem wait 10 seconds
ping 127.0.0.1 -n 10 > nul


pushd . 
cd .\AgentViews
start MTConnectPagelocalhost80.vbs
start MTConnectPagelocalhost81.vbs
popd


pushd .
cd .\AgentCmd
start ShdrCommandCell.exe
popd


rem start .\SSH\startallherbie.vbs


