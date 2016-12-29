#include "common.h"

void handler_int(int signum)
{
	printf("this is int\n");
}

void handler_quit(int signum)
{
	printf("this is quit\n");
}

int main()
{
	signal(SIGINT, handler_int);
	signal(SIGQUIT, handler_quit);

	while(1)
		sleep(1);

	return 0;
}
