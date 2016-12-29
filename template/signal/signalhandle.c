#include "common.h"
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

void handle(int signum)
{
	if(signum == SIGINT)
		printf("this is sigint\n");
}

int main()
{
	signal(SIGINT, handle);
	while(1)
	{
		sleep(1);
		printf("hi\n");
	}
	return 0;
}
