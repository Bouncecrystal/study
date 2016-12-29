#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

typedef struct list    //定义歌词数据结构
{
	char song[50];
	int num;
}List;

void get_list();

void make_fifo();

void play_mplayer();

void command();