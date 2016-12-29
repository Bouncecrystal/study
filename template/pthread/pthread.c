#include "common.h"
#include <pthread.h>

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex3 = PTHREAD_MUTEX_INITIALIZER;

void* fun1(void* temp)
{
	while(1)
	{
		pthread_mutex_lock(&mutex1);
		DEBUG("a\n");
		sleep(1);
		pthread_mutex_unlock(&mutex2);
	}
	return NULL;
}	

void* fun2(void* temp)
{
	while(1)
	{
		pthread_mutex_lock(&mutex2);
		DEBUG("b\n");
		sleep(1);
		pthread_mutex_unlock(&mutex3);
	}
	return NULL;
}

void* fun3(void* temp)
{
	while(1)
	{
		pthread_mutex_lock(&mutex3);
		DEBUG("c\n");
		sleep(1);
		pthread_mutex_unlock(&mutex1);
	}
	return NULL;
}

int main()
{
	pthread_t thread1, thread2, thread3;

	pthread_mutex_unlock(&mutex1);
	pthread_mutex_lock(&mutex2);
	pthread_mutex_lock(&mutex3);

	pthread_create(&thread1, NULL, fun1, NULL);
	pthread_create(&thread2, NULL, fun2, NULL);
	pthread_create(&thread3, NULL, fun3, NULL);
	
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);

	pthread_mutex_destroy(&mutex1);
	pthread_mutex_destroy(&mutex2);
	pthread_mutex_destroy(&mutex3);

	return 0;
}
