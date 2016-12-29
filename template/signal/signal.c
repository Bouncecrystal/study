#include "common.h"

void handler(int signum)
{
	printf("b can not be zero\n");
}

int main()
{
	int a=1, b=0;
	struct sigaction sa_in;
	struct sigaction sa_out;

	sigaction(SIGFPE, NULL, &sa_out);

	sa_in.sa_handler = handler;
	sa_in.sa_mask = sa_out.sa_mask;
	sa_in.sa_flags = sa_out.sa_flags;

	sigaction(SIGFPE, &sa_in, NULL);
	
	printf("%d", a/b);
	
	return 0;
}
