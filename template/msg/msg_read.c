#include "common.h"
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

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
	MSG msg;

	key = ftok("./", 2016);
	msqid = msgget(key, IPC_CREAT | 0666);
	printf("msqid:%d\n", msqid);
	if(msqid < 0)
		err_sys("msgget error");
	
	memset(msg.name, 0, 20);
	msgrcv(msqid, &msg, sizeof(msg)-sizeof(msg.type), 1, 0);

	printf("%ld\n%s\n%d\n%d\n%d\n", msg.type, msg.name, msg.birthday, msg.height, msg.weight);

	ret = msgctl(msqid, IPC_RMID, NULL);
	if(ret < 0)
		err_sys("msgctl error");

	return 0;
}
