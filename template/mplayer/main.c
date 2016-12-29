#include "mplayer.h"

List list[50];

int main()
{
	int pid;
	get_list();
	make_fifo();

	pid = fork();
	if(pid < 0)
		printf("fork error");
	else if(0 == pid)
	{
		//mplayer.c
		play_mplayer();
	}
	else
	{
		//command.c
		command();
		wait(NULL);
	}

	return 0;
}

