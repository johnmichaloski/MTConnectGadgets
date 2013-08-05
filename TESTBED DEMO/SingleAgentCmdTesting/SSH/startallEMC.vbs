

Dim objShell
Dim cmd1, cmd2, strPath, objFSO, objFile, strFolder

Set objShell = CreateObject("WScript.Shell")

strPath = Wscript.ScriptFullName

Set objFSO = CreateObject("Scripting.FileSystemObject")

Set objFile = objFSO.GetFile(strPath)
strFolder = objFSO.GetParentFolderName(objFile) 

cmd1 = "ssh  simuser@minnie -i" &  Chr(34) & "/cygdrive/c/Documents and Settings/simuser/My Documents/.ssh/id_rsa"&  Chr(34) & " /home/simuser/start.sh -p 7878 --currenturl http://pluto:81/CNC1_RESOURCE/current"
'cmd2 = "ssh  simuser@herbie -i" &  Chr(34) & "/cygdrive/c/Documents and Settings/simuser/My Documents/.ssh/id_rsa"&  Chr(34) & " /usr/local/proj/gomotion/bin/spinup -p 7879 -s  pluto -c pluto:81 -m CNC2_RESOURCE << password1 EOF"



objShell.run(cmd1)
'objShell.run(cmd2)


'ssh  simuser@monstro -i "/cygdrive/c/Documents and Settings/simuser/My Documents/.ssh/id_rsa" "/usr/local/proj/gomotion/bin/mtcrun -i /usr/local/proj/gomotion/etc/genhex1.ini -p 7878  "