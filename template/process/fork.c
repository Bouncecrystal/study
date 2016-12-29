#include "common.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

int main()
{
	int fd;
	pid_t pid;
	
	fd=open("test.data", O_RDWR| O_CREAT| O_TRUNC, 0666);
	if(fd < 0)
		err_sys("open error");
	dup2(fd, 1);

	pid = fork();
	if(pid < 0)
		err_sys("fork error");
	else if(pid == 0)
	{
		printf("hello");
	}
	else
	{
		sleep(1);
		printf("world");
		wait(NULL);
	}
	return 0;
}
