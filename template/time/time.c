#include "common.h"
#include <time.h>
#include <sys/time.h>

int main()
{
	struct timeval tv1, tv2;
	gettimeofday(&tv1, NULL);
	
	time_t now = time(NULL); //��ȡ����ʱ��
	printf("now is %ld\n", now);
	
	struct tm *utc = gmtime(&now); //������ʱ��ת����UTCʱ��
	printf("hour is:%d\nmin is:%d\nsec is:%d\n", 
		utc->tm_hour,
		utc->tm_min,
		utc->tm_sec);
	printf("UTC is:%s\n", asctime(utc));//ʱ��ṹ��ת����ʱ���ַ���
		
	struct tm *local = localtime(&now);//������ʱ��ת������ʱ��ṹ��
	printf("hour is:%d\nmin is:%d\nsec is:%d\n", 
		local->tm_hour,
		local->tm_min,
		local->tm_sec);
	printf("LOCAL is:%s\n", asctime(local));
	printf("LOCAL is:%s\n", ctime(&now));
	sleep(1);
	
	gettimeofday(&tv2, NULL);
	
	//����ʱ����msΪ��λ
	printf("grogram run %ld ms\n", (tv2.tv_sec - tv1.tv_sec) * 1000 + \
		(tv2.tv_usec - tv1.tv_usec) / 1000);
	
	return 0;
}
