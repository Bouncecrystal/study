#include "common.h"

int main()
{
	int ret;
	int fd[2];
	ret = pipe(fd);
	if(ret < 0)
		err_sys("pipe error");

	pid_t pid;
	pid = fork();
	if(pid < 0)
		err_sys("fork error");
	else if(0 == pid)  //读
	{
		close(fd[1]); fd[1] = -1;
		fcntl(fd[0], F_SETFL, O_NONBLOCK);
		while(1)
		{
			int n;
			char buff[1024];
			n = read(fd[0], buff, sizeof(buff));
			buff[n] = '\n';
			printf("%s\n", buff);
		}
		exit(0);
	}
	else               //写
	{
		close(fd[0]); fd[0] = -1;
		while(1)
		{
			char buff[1024];
			fgets(buff, 1024, stdin);
			write(fd[1], buff, sizeof(buff));
		}
		exit(0);
	}

	return 0;
}
