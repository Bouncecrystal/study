#include "common.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	pid_t pid;

	pid = vfork();
	if(pid < 0)
		err_sys("vfork error");
	else if(pid == 0)
	{
		execl("/bin/ps", "ps", "ax", (char*)0);
	}
	else
	{
		printf("this is parent\n");
		wait(NULL);
	}

	return 0;
}
