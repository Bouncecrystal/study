#include "common.h"
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char** argv)
{
	if(argc != 3)
		err_quit("usage:./udp_send address port");

	int socketfd;
	struct sockaddr_in send_addr;
	
	socketfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(socketfd < 0)	
		err_sys("socket error");

	send_addr.sin_family = AF_INET;
	send_addr.sin_port = htons(atoi(argv[2]));
	inet_pton(AF_INET, argv[1], &send_addr.sin_addr.s_addr);

	int fd;
	fd = open("./0.dix", O_RDONLY);
	printf("%d\n", fd);

	for(;;)
	{	
		int n;
		char buffer[1024];
		
		//fgets(buffer, 1024, stdin);
		n = read(fd, buffer, 1024);
		printf("%d\n", n);
		if(n <= 0)
		break;		

		sendto(socketfd, buffer, n, 0, (struct sockaddr*)&send_addr, sizeof(send_addr));
	}

	close(fd);
	close(socketfd);
	
	return 0;
}
