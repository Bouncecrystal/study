#include "mplayer.h"
#include <dirent.h>

extern List list[50];

void get_list()
{
	int i, n, ret;
	DIR* dir;
	struct dirent* p;
	
	dir = opendir("./");	//打开当前文件夹
	if(dir == NULL)
		printf("opendir error");
	printf("song list:\n");
	while(1)	//读取.mp3文件存至list中并打印列表
	{
		p = readdir(dir);
		if(p == NULL)
			break;
		if(p->d_ino == -1)
			printf("readdir error");
		else
		{
			n = strlen(p->d_name);
			if(p->d_name[n-1] == '3'\
				&& p->d_name[n-2] == 'p'\
				&& p->d_name[n-3] == 'm'\
				&& p->d_name[n-4] == '.')
			{
				/*list[i].num = i;
				ret = strncpy(list[i].song, p->d_name, n-4);
				list[i].song[ret] = '\0';
				printf("%d %s\n", list[i].num, list[i].song);
				++i;*/
				printf("%s\n", p->d_name);
			}
		}
	}
	closedir(dir);	//关闭当前文件夹
}

