#include "mplayer.h"

void make_fifo()
{
	int ret = access("myfifo", F_OK);
	if(ret == 0)
		return;
	else
		mkfifo("myfifo", 0666);
}