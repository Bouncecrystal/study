#include "common.h"
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char** argv)
{
	if(argc != 3)
		err_quit("usage:./udp_recv address port");

	int socketfd;
	int ret;
	struct sockaddr_in recv_addr;

	socketfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(socketfd < 0)
		err_sys("socket error");

	recv_addr.sin_family = AF_INET;
	recv_addr.sin_port = htons(atoi(argv[2]));
	inet_pton(AF_INET, argv[1], &recv_addr.sin_addr);

	ret = bind(socketfd, (struct sockaddr*)&recv_addr, sizeof(recv_addr));
	if(ret < 0)
		err_sys("bind error");

	int fd;
	fd = open("./text", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	printf("%d\n", fd);
	
	for(;;)
	{
		int n;
		char str[16];
		char buffer[1024];
		struct sockaddr_in addr;
		socklen_t len = sizeof(addr);
		
		n = recvfrom(socketfd, buffer, 1024, 0, (struct sockaddr*)&addr, &len);
		
		inet_ntop(AF_INET, &addr.sin_addr, str, 16); 

			printf("address:%s\n", str);
			printf("port:%d\n", ntohs(addr.sin_port));
			printf("%s\n", buffer);	

			write(fd, buffer, n);
	
	}

	close(fd);

	return 0;
}
