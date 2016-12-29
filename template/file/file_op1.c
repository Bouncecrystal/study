#include "common.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main()
{
	int fd = open("test.data", O_RDWR | O_CREAT | O_EXCL, 0666);
	char buffer;
	char s[20] = "1234\n2234\0";

	if(fd < 0)
	{
		fd = open("test.data", O_RDONLY);
		while(buffer != '\n')
		{
			read(fd, &buffer, 1);
			write(1, &buffer, 1);
		}	
	}
	else
	{
		write(fd, s, sizeof(s));
	}
	close(fd);

	return 0;
}
