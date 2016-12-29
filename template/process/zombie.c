#include "common.h"
#include <unistd.h>

int main()
{
	pid_t pid;

	pid = fork();
	if(pid < 0)
		err_sys("fork error");
	else if(pid == 0)
	{
		
	}
	else
	{
		sleep(2);
		system("ps -ax");
	}
	return 0;
}
