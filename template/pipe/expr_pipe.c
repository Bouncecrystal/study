#include "common.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

int main()
{
	int fd[2];
	int ret1 = pipe(fd);
	if(ret1 < 0)
		err_sys("pipe error");

	pid_t pid=fork();
	if(pid < 0)
		err_sys("fork error");
	else if(0 == pid)  //write
	{
		int flags = fcntl(fd[1], F_GETFD);
		flags &= ~FD_CLOEXEC;
		fcntl(fd[1], F_SETFD, flags);
		int ret2 = dup2(1, fd[1]);
		if(ret2 < 0)
			err_sys("dup2 error1");
		execlp("expr", "expr", "5", "+", "4", (char*)0);
		exit(0);
	}
	else  //read
	{
		sleep(1);
		char a[1000];
		int n = read(fd[0], a, 1000);
		printf("n=%d", n);
		a[n] = '\0';
		printf("%s\n", a);
		exit(0);
	}

	return 0;
}
