#include "common.h"
#include <string.h>

int main()
{
	int fd1,fd2;
	pid_t pid = fork();
	if(pid < 0)
		err_sys("fork error");
	else if(0 == pid)    //write
	{
		fd1 = open("./myfifo", O_WRONLY);
		char buffer1[1024];
		while(1)
		{
			bzero(buffer1, 1024);
			fgets(buffer1, 1024, stdin);
			close(fd2);
			write(fd1, buffer1, strlen(buffer1));
		}
	}
	else				//read
	{	
		char buffer2[1024];
		while(1)
		{
			fd2 = open("./myfifo", O_RDONLY);
			bzero(buffer2, 1024);
			int n = read(fd2, buffer2, 1024);
			if(n < 0)
			{
				sleep(1);
				continue;
			}
			printf("%s", buffer2);
		}
	}

	return 0;
}
