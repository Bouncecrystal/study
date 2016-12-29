#include "common.h"
#include <sys/ipc.h>
#include <sys/msg.h>

typedef struct msg{
	long type;
	char text[100];
	char name[20];
}MSG;

int main()
{
	key_t key = ftok("./", 2016);
	int msqid = msgget(key, IPC_CREAT | 0666);
	pid_t pid = fork();
	if(pid < 0)
		err_sys("fork error");
	else if(0 == pid)
	{
		while(1)
		{
			MSG msg_snd;
			scanf("%ld", &msg_snd.type);
			scanf("%s", msg_snd.text);
			scanf("%s", msg_snd.name);
	
			int ret = msgsnd(msqid, &msg_snd, sizeof(msg_snd)-sizeof(msg_snd.type), 0);
			if(ret < 0)
				err_sys("msgsnd error");
		}
	}
	else  
	{
		while(1)
		{
			MSG msg_rcv;
			msgrcv(msqid, &msg_rcv, sizeof(msg_rcv)-sizeof(msg_rcv.type), 1, 0);
			printf("text is:%s\nfrom:%s\n", msg_rcv.text ,msg_rcv.name);
		}
	}

	return 0;
}
