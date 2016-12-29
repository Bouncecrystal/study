#include "common.h"
#include <fcntl.h>
#include <errno.h>

int main()
{
	int n, fd;
	char buffer[1024];

	fd = open("myfifo", O_RDONLY);
   //	fcntl(fd, F_SETFL, O_NONBLOCK);
	if(fd < 0)
		err_sys("open error");
	while(1)
	{
		n = read(fd, buffer, 1024);
		if(n < 0)
		{
			if(errno == EAGAIN || errno == EWOULDBLOCK)
			{
				printf("no data");
				sleep(1);
			}
			else
				err_sys("read error");
		}
		else
		{
			buffer[n] = '\0';
			DEBUG("%s\n", buffer);
			sleep(1);
		}
	}
	
	return 0;
}
