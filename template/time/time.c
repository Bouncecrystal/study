#include "common.h"
#include <time.h>
#include <sys/time.h>

int main()
{
	struct timeval tv1, tv2;
	gettimeofday(&tv1, NULL);
	
	time_t now = time(NULL); //获取日历时间
	printf("now is %ld\n", now);
	
	struct tm *utc = gmtime(&now); //将日历时间转换成UTC时间
	printf("hour is:%d\nmin is:%d\nsec is:%d\n", 
		utc->tm_hour,
		utc->tm_min,
		utc->tm_sec);
	printf("UTC is:%s\n", asctime(utc));//时间结构体转换成时间字符串
		
	struct tm *local = localtime(&now);//将日历时间转换本地时间结构体
	printf("hour is:%d\nmin is:%d\nsec is:%d\n", 
		local->tm_hour,
		local->tm_min,
		local->tm_sec);
	printf("LOCAL is:%s\n", asctime(local));
	printf("LOCAL is:%s\n", ctime(&now));
	sleep(1);
	
	gettimeofday(&tv2, NULL);
	
	//计算时间差，以ms为单位
	printf("grogram run %ld ms\n", (tv2.tv_sec - tv1.tv_sec) * 1000 + \
		(tv2.tv_usec - tv1.tv_usec) / 1000);
	
	return 0;
}
