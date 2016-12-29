#include "common.h"

int a = 1;

void handler1(int sigum)
{
	a=5;
	DEBUG("this is alarm:a=%d", a);

}
void handler2(int sigum)
{
	sigset_t set;

	sigprocmask(SIG_BLOCK, NULL, &set);
	sigaddset(&set, SIGALRM);
	sigprocmask(SIG_SETMASK, &set, NULL);
	a=0;
	DEBUG("this is int:%d", a);
	sleep(10);
}

int main()
{
	pid_t pid = fork();
	if(pid < 0)
		err_sys("fork error");
	else if(0 == pid)
	{
		for(;;)
		{
			sleep(3);
			kill(getppid(), SIGALRM);
		}
	}
	else
	{
		signal(SIGALRM, handler1);
		signal(SIGINT, handler2);
		for(;;)
		{
			DEBUG("%d\n", a);
			sleep(1);
		}
	}
	return 0;
}
