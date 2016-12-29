#include "mplayer.h"

void play_mplayer()
{	
	execlp("mplayer",
				"mplayer",\
				"-slave", "-quiet", "-idle",\
				"-input","file=./myfifo",\
				"./heyjudy.mp3",\
				"./",\
				(char*)0);
				
	open("myfifo", O_RDONLY);
}