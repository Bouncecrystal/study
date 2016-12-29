#include "common.h"

int main()
{
	int fd;
	char buffer[1024]="hello";

	fd = open("myfifo", O_WRONLY);
	if(fd < 0)
		err_sys("open error");
	while(1)
	{
		write(fd, buffer, sizeof(buffer));
		sleep(2);
	}

	return 0;
}
