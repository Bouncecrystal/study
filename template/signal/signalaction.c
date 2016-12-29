#include "common.h"
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

void handler(int signum)
{
	DEBUG("this is sigalrm:%d\n", signum);
	alarm(5);
}

int main()
{
	struct sigaction sa_out;
	struct sigaction sa_in;

	sa_in.sa_handler = handler;

	sigaction(SIGALRM, NULL, &sa_out);
	sigset_t ss;
	ss = sa_out.sa_mask;
	sigaddset(&ss, SIGINT);
	sa_in.sa_mask = ss;

	sa_in.sa_flags = sa_out.sa_flags;

	sigaction(SIGALRM, &sa_in,	NULL);

	alarm(5);
	while(1)
		sleep(1);

	return 0;
}
