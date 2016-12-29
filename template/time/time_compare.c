#include "common.h"
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	int i = 0;
	long int t1, t2, t3, t4;

	struct timeval time1; 
	gettimeofday(&time1, NULL);
	for(i=0; i<1000; i++)
		printf("hello");
	struct timeval time2;
	gettimeofday(&time2, NULL);

	struct timeval time3;
	gettimeofday(&time3, NULL);
	for(i=0; i<1000; i++)
		write(1, "hello", 6);
	struct timeval time4;
	gettimeofday(&time4, NULL);

	t1=time1.tv_sec * 1000000 + time1.tv_usec;
	t2=time2.tv_sec * 1000000 + time2.tv_usec;	
	t3=time3.tv_sec * 1000000 + time3.tv_usec;
	t4=time4.tv_sec * 1000000 + time4.tv_usec;

	printf("%ld\n%ld\n", t2-t1, t4-t3);

	return 0;
}
