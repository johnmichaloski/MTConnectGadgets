

Dim objShell
Dim cmd1, cmd2, cmd3, cmd4, cmd5, cmd6, strPath, objFSO, objFile, strFolder

Set objShell = CreateObject("WScript.Shell")

strPath = Wscript.ScriptFullName

Set objFSO = CreateObject("Scripting.FileSystemObject")

Set objFile = objFSO.GetFile(strPath)
strFolder = objFSO.GetParentFolderName(objFile) 


cmd1 = "ssh  simuser@herbie -i" &  Chr(34) & "/cygdrive/c/Documents and Settings/simuser/My Documents/.ssh/id_rsa"&  Chr(34) & "  /usr/local/proj/gomotion/bin/killgo "

objShell.run(cmd1)

