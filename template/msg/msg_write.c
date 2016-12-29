#include "common.h"
#include <sys/ipc.h>
#include <sys/msg.h>

typedef struct{
	long type;
	char name[20];
	int birthday;
	int height;
	int weight;
}MSG;

int main()
{
	key_t key;
	int msqid;
	int ret;

	key = ftok("./",2016);
	msqid = msgget(key, IPC_CREAT | 0666);
	if(msqid < 0)
		err_sys("msgget error");
	MSG msg;
	msg.type = 1;
	strcpy(msg.name, "llz");
	printf("%s",msg.name);
	msg.birthday = 19940213;
	msg.height = 175;
	msg.weight = 80;

	ret = msgsnd(msqid, &msg, sizeof(msg)-sizeof(msg.type), 0);
	if(ret < 0)
		err_sys("msgsnd error");

	return 0;
}
