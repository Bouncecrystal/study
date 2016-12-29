#include "common.h"

void handler(int signum)
{
	DEBUG("this is sigint\n");
	signal(SIGINT, SIG_DFL);
}

int main()
{
	signal(SIGINT, handler);
	for(;;)
	{
		printf("hello\n");
		sleep(1);
	}
	return 0;
}
