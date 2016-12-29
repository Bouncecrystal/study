#include "common.h"
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

int main()
{
	sigset_t set;

	sigprocmask(SIG_BLOCK, NULL, &set);
	sigaddset(&set, SIGINT);
	sigprocmask(SIG_BLOCK, &set, NULL);

	for(int i=0; i<5; i++)
	{
		printf("hello\n");
		sleep(1);
	}

	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigprocmask(SIG_UNBLOCK, &set, NULL);

	while(1)
	{
		printf("hehheheheh");
	}		
	return 0;
}
