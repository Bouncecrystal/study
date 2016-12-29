#include "common.h"
#include <sys/ipc.h>
#include <sys/shm.h>

int main()
{
	int ret;
	int shmid;
	char* shmaddr;
	key_t key;

	key = ftok("./", 2016);

	shmid = shmget(key, 1024, IPC_CREAT | 0666);
	if(shmid < 0)
		err_sys("shmget error");
	
	shmaddr = shmat(shmid, NULL, 0);
	if(shmaddr < 0)
		err_sys("shmat error");
	
	strcpy(shmaddr, "this is shm");

	ret = shmdt(shmaddr);
	if(ret < 0)
		err_sys("shmdt error");

	return 0;
}
