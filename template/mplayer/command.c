#include "mplayer.h"

void command()
{
	int fd;
	
	fd = open("myfifo", O_WRONLY);
	dup2(1, fd);
	gets();
}