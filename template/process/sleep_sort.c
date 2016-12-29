#include "common.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define N 1000

int main()
{
	int i;
	pid_t pid;
	int data[N]; // = {1, 2, 7 ,6 ,5 ,4, 3 ,8 ,9, 10};

	for(i = 0; i < N; i++)
		data[i] = random() % N;

	for(i = 0; i < N; i++)
	{
		pid = fork();
		if(pid < 0)
			err_sys("fork error");
		else if(pid == 0)
		{
			usleep(data[i]*100000);
			printf("%d\n", data[i]);
			exit(1);
		}
		else
			continue;
	}
	return 0;
}
