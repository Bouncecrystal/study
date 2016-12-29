#include "common.h"
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char **argv)
{
	if(argc != 3)
		err_quit("usage:./tcp_client ip port");
	
	int ret1, ret2, ret3;
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

		fd_set read_set;
		int flag = 0;
		//recv
		for(;;)
		{
			int n;
			char buffer[1024];
			FD_ZERO(&read_set);
			FD_SET(0, &read_set);
			if(flag == 0)
				FD_SET(clifd, &read_set);
			ret3 = select(clifd + 1, &read_set, NULL, NULL, NULL);
			if(ret3 < 0)
				err_sys("select error");
			else
			{
				if(FD_ISSET(0, &read_set))
				{
					bzero(buffer, sizeof(buffer));
					n = read(0, buffer, 1024);
					buffer[n] = '\0';
					write(clifd, buffer, 1024);
				}
				if(FD_ISSET(clifd, &read_set))
				{
					bzero(buffer, sizeof(buffer));	
					n = recv(clifd, buffer, sizeof(buffer), 0);

					if(n < 0)
						break;
					if(n == 0)
					{
						printf("disconnect\n");
						break;
					}
					if(strncmp(buffer, "stop", strlen("stop")) == 0)
						//flag = 1;
						shutdown(clifd, SHUT_RD);
					else
					{
						buffer[n] = '\0';
						printf("%s\n", buffer);
					}
				}	
			}	
		}
	}
	

	return 0;
}













