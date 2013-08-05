

Dim objShell
Dim cmd1, cmd2, strPath, objFSO, objFile, strFolder, cmd3a, cmd3b, cmd4

Set objShell = CreateObject("WScript.Shell")

strPath = Wscript.ScriptFullName

Set objFSO = CreateObject("Scripting.FileSystemObject")

Set objFile = objFSO.GetFile(strPath)
strFolder = objFSO.GetParentFolderName(objFile) 

cmd1 = "ssh  simuser@herbie -i" &  Chr(34) & "/cygdrive/c/Documents and Settings/simuser/My Documents/.ssh/id_rsa"&  Chr(34) & " /usr/local/proj/gomotion/bin/spinup  -p 7878 -s  pluto -c pluto:81 -m CNC1_RESOURCE"
cmd2 = "ssh  simuser@herbie -i" &  Chr(34) & "/cygdrive/c/Documents and Settings/simuser/My Documents/.ssh/id_rsa"&  Chr(34) & " /usr/local/proj/gomotion/bin/spinup  -p 7879 -s  pluto -c pluto:81 -m CNC2_RESOURCE"
cmd3a = "ssh  simuser@herbie -i" &  Chr(34) & "/cygdrive/c/Documents and Settings/simuser/My Documents/.ssh/id_rsa"&  Chr(34) & " /usr/local/proj/gomotion/bin/spinup  -p 7880 -s  pluto -c pluto:81 -m CNC3Old_RESOURCE"
cmd3b = "ssh  simuser@herbie -i" &  Chr(34) & "/cygdrive/c/Documents and Settings/simuser/My Documents/.ssh/id_rsa"&  Chr(34) & " /usr/local/proj/gomotion/bin/spinup  -p 7881 -s  pluto -c pluto:81 -m CNC3New_RESOURCE"
cmd4 = "ssh  simuser@herbie -i" &  Chr(34) & "/cygdrive/c/Documents and Settings/simuser/My Documents/.ssh/id_rsa"&  Chr(34) & " /usr/local/proj/gomotion/bin/spinup  -p 7882 -s  pluto -c pluto:81 -m CNC4_RESOURCE"



objShell.run(cmd1)
objShell.run(cmd2)
objShell.run(cmd3a)
objShell.run(cmd3b)
objShell.run(cmd4)


'ssh  simuser@monstro -i "/cygdrive/c/Documents and Settings/simuser/My Documents/.ssh/id_rsa" "/usr/local/proj/gomotion/bin/mtcrun -i /usr/local/proj/gomotion/etc/genhex1.ini -p 7878  "