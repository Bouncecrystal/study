#include "common.h"
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char **argv)
{
	if(argc != 3)
		err_quit("usage:./tcp_client ip port");
	
	int ret1, ret2;
	int sockfd;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
		err_sys("socket error");
	
	//bind
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(argv[2]));
	inet_pton(AF_INET, argv[1], &addr.sin_addr);
	ret1 = bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));	
	if(ret1 < 0)
		err_sys("bind error");
	ret2 = listen(sockfd, 2);
	if(ret2 < 0)
		err_sys("listen error");
	
	//accept
	for(;;)
	{
		int clifd;
		char ip[16];
		struct sockaddr_in cliaddr;
		socklen_t len = sizeof(cliaddr);
		clifd = accept(sockfd, (struct sockaddr*)&cliaddr, &len);

		inet_ntop(AF_INET, &cliaddr.sin_addr, ip, sizeof(ip));
		printf("connect with ip %s  port %d\n", ip, ntohs(cliaddr.sin_port));

		//recv
		for(;;)
		{
			int n;
			char buffer[1024];
					
			n = recv(clifd, buffer, sizeof(buffer), 0);

			if(n < 0)
				break;
			if(n == 0)
			{
				close(clifd);
				printf("disconnect\n");
				break;
			}
			else
			{
				buffer[n] = '\0';
				printf("%s\n", buffer);
			}		
		}
	}
	

	return 0;
}













