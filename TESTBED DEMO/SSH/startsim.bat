
SET variable=password1

ssh simuser@monstro -i "/cygdrive/c/Documents and Settings/simuser/My Documents/.ssh/id_rsa"  /usr/local/proj/gomotion/testing/startmtc.sh -i /usr/local/proj/gomotion/etc/genhex1.ini -p 7878 
<< %variable%  

pause

ssh simuser@monstro -i "/cygdrive/c/Documents and Settings/simuser/My Documents/.ssh/id_rsa"  /usr/local/proj/gomotion/testing/startmtc.sh -i /usr/local/proj/gomotion/etc/genhex2.ini -p 7879 
<< %variable% &

pause 

ssh  simuser@monstro -i "/cygdrive/c/Documents and Settings/simuser/My Documents/.ssh/id_rsa"  /usr/local/proj/gomotion/testing/startmtc.sh -i /usr/local/proj/gomotion/etc/genhex3.ini -p 7880 
<< %variable% &

pause 