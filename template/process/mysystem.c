#include "common.h"
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char* argv[])
{
	if(argc == 1)
		err_sys("Usage:./mysystem command");
	
	int ret;
	pid_t pid;

	pid = vfork();
	if(pid < 0)
		err_sys("vfork error");
	else if(pid == 0)
	{
		ret = execl("/bin/sh", "sh", "-c", argv[1], argv[2], (char*)0);
		if(ret < 0)
		{
			err_sys("execv error");
		}
	}
	else
	{
		int status;
		wait(&status);
		if(WIFEXITED(status) != 0)
			printf("end normally:%d\n", WEXITSTATUS(status));
		else
			printf("end unusual:%d\n",WIFSTOPPED(status));
	}

	return 0;
}
