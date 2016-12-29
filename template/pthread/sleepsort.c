#include "common.h"
#include <pthread.h>

void* fun(void* temp)
{
	sleep(*(int*)temp);
	printf("%d\n", *(int*)temp);
	return 0;
}

int main()
{	
	int i, ret;
	int num[100];
	pthread_t thread[100];

	for(i = 0; i<100; i++)
	{
		num[i] = rand()%100;
		ret = pthread_create(&thread[i], NULL, fun, (void*)&num[i]);//创建thread
		if(ret != 0)
			err_sys("pthread_create error");
		//pthread_detach(thread[i]);

	}
	sleep(100);
	return 0;
}
