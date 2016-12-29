#include "common.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char* argv[])
{
	if(argc != 3)
		err_quit("usage:./cpfile src dst\n");
	
	int n;
	char buffer[1024];
	int fd_src;
	int fd_dst;

	fd_src=open(argv[1], O_RDONLY);
	fd_dst=open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0666);

	if(fd_src < 0 && fd_dst < 0)
		printf("open error\n");

	while((n = read(fd_src, buffer, sizeof(buffer))) != 0)
	{
		write(fd_dst, buffer, n);
	}

	close(fd_src);
	close(fd_dst);
	return 0;
}
