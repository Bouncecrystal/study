#include "common.h"

void handler(int sigum)
{
	DEBUG("get a sigalrm");
	kill(getpid(), SIGKILL);
}

int main()
{
	pid_t pid = fork();
	if(pid < 0)
		err_sys("fork error");
	else if(0 == pid)
	{
		sleep(5);
		kill(getppid(), SIGALRM);
	}
	else
	{
		signal(SIGALRM, handler);
		pause();
	}
	return 0;
}
