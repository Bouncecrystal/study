#include "common.h"
#include <sys/ipc.h>
#include <sys/shm.h>

int main()
{
	char buffer[1024];
	int ret1,ret2;
	int shmid;
	key_t key;
	char* shmaddr;

	key = ftok("./", 2016);

	shmid = shmget(key, 1024, IPC_CREAT | 0666);
	if(shmid < 0)
		err_sys("shmget error");
	
	shmaddr = shmat(shmid, NULL, 0);
	if(shmaddr < 0)
		err_sys("shmat error");

	strcpy(buffer, shmaddr);
	printf("%s\n", buffer);

	ret1 = shmdt(shmaddr);
	if(ret1 < 0)
		err_sys("shmdt error");

	ret2 = shmctl(shmid, IPC_RMID, NULL);
	if(ret2 < 0)
		err_sys("shmctl error");

	return 0;
}
