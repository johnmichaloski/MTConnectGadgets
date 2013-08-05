
THIS HAS TO BE PARSED:

ssh-agent
SSH_AUTH_SOCK=/tmp/ssh-fN0KgRUcE8Hy/agent.1056; export SSH_AUTH_SOCK;
SSH_AGENT_PID=1068; export SSH_AGENT_PID;
echo Agent pid 1068;

THen this has to be output:

set SSH_AUTH_SOCK=/tmp/ssh-fN0KgRUcE8Hy/agent.
set SSH_AGENT_PID=1068

ssh-add ".ssh\id_rsa"
pause
ssh monstro ls < "yes"
pause
ssh monstro /usr/local/proj/gomotion/testing/startmtc.sh -i /usr/local/proj/gomotion/etc/genhex1.ini -p 7878

